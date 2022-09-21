#include<stdio.h>
#include<string.h>
#include<mysql.h>

struct node
{
    char product_name[30];
    int  count;
    char item_id[30];
};

void bill_to_file(MYSQL* connection)
{
    MYSQL_RES *result_set;
    MYSQL_ROW row;
    int row_count = 0;
    char space[17] = "             ";
    char query[400] = "";
    int  net=0;
    int  total=0;
    char timestamp[50]="";
    struct node list[50];
    int id=0,i=0;

    FILE *fptr = fopen("bill.txt","w");
    //mysql_free_result(result_set);
    sprintf(query,"select current_timestamp()");
    if(mysql_query(connection, query))
    {
        fprintf(stderr, "%s\n", mysql_error(connection));
        mysql_close(connection);
        exit(1);
    }
    result_set = mysql_use_result(connection);
    row = mysql_fetch_row(result_set);

    strcpy(timestamp,row[0]);
    mysql_free_result(result_set);

    sprintf(query, "select * from cart");
    if(mysql_query(connection, query))
    {
        fprintf(stderr, "%s\n", mysql_error(connection));
        mysql_close(connection);
        exit(1);
    }

    result_set = mysql_use_result(connection);

    do
    {
        row = mysql_fetch_row(result_set);

        if(!row)
            break;
        else if(row_count == 0)
        {
            fprintf(fptr,"\n\n\n\n%s+---------------------------------------------------------------------------------+\n",space);
            fprintf(fptr,"%s|                             INVOICE:  %-30s            |\n",space,timestamp);
            fprintf(fptr,"%s+---------------------------------------------------------------------------------+\n",space);
            fprintf(fptr,"%s|  S.No  | PRODUCT NAME | BRAND NAME | BRAND MODEL |   PRICE   | COUNT |   Bill   |\n",space);
            fprintf(fptr,"%s+--------+--------------+------------+-------------+-----------+-------+----------+\n",space);
        }
        memset(list[id].product_name,'\0',30);
        strcpy(list[id].product_name,row[0]);
        list[id].count = atoi(row[4]);
        memset(list[id].item_id,'\0',30);
        strcpy(list[id].item_id,row[5]);
        net = atoi(row[4])*atoi(row[3]);
        total += net;
        fprintf(fptr,"%s| %-6d | %-12s | %-10s | %-11s |  %-7s  | %-5s | %-8d |\n",space,row_count+1,row[0],row[1],row[2],row[3],row[4],net);
        //sprintf(query,"update %s set count = count - %d where item_id = '%s'",row[0],atoi(row[4]),row[5]);
        //if(mysql_query(connection, query))
        //{
        //    fprintf(stderr, "%s\n", mysql_error(connection));
        //    mysql_close(connection);
        //    exit(1);
        //} 
        id++;
        row_count++;
    }
    while(1);
    mysql_free_result(result_set);
    while(i<id)
    {
        sprintf(query,"update %s set count = count - %d where item_id = '%s'",list[i].product_name,list[i].count,list[i].item_id);
        if(mysql_query(connection, query))
        {
            fprintf(stderr, "%s\n", mysql_error(connection));
            mysql_close(connection);
            exit(1);
        }
        i++;
    }
    if(row_count)
    {
        sprintf(query,"%10.2f",((float)total*(float)(106))/(float)100);
        fprintf(fptr,"%s+---------------------------------------------------------------------------------+\n",space);
        fprintf(fptr,"%s|                          Total Bill with 6%% sales tax - $%-12s           |\n",space,query);
        fprintf(fptr,"%s+---------------------------------------------------------------------------------+\n\n\n\n\n",space);
    }
}
