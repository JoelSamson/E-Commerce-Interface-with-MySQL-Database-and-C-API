#include<stdio.h>
#include<string.h>
#include<mysql.h>

extern void display_product_list(MYSQL*); 
int  display_laptop_inventory(MYSQL*);
int  display_Refrigerator_inventory(MYSQL*);
int  display_item_inventory(MYSQL*, char*);
int  display_phone_inventory(MYSQL*);
void input_serial_no(char*);

int display_phone_inventory(MYSQL* connection)
{
    MYSQL_RES *result_set;
    MYSQL_ROW row;
    int row_count = 0;
    //char space[17] = "             ";
    char query[100] = "";

    sprintf(query, "select * from Phone order by id");
    printf("\e[1;1H\e[2J");
    printf("\n\n\n\n");
    if (mysql_query(connection, query))
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
            printf("\n\n\n\n");
            printf("+--------+------------+-------------+-----------------+------------------+------------+------------+------------+-------------+--------------+---------+\n");
            printf("|                                                               PRODUCT PHONE                                                                          |\n");
            printf("+--------+------------+-------------+-----------------+------------------+------------+------------+------------+-------------+--------------+---------+\n");
            printf("|  S.No  | BRAND NAME | BRAND MODEL |    PROCESSOR    | OPERATING SYSTEM |  CELLULAR  |   COLOUR   |  CARRIER   | SCREEN SIZE |    PRICE     |  COUNT  |\n");
            printf("+--------+------------+-------------+-----------------+------------------+------------+------------+------------+-------------+--------------+---------+\n"); 
        }
         printf("| %-6s | %-10s | %-11s | %-15s |    %-10s    | %-10s | %-10s | %-10s |   %-7s   | %-12s | %-7s |\n",row[10],row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9]);
        row_count++;
    }
    while(1);

    if(row_count)
        printf("+--------+------------+-------------+-----------------+------------------+------------+------------+------------+-------------+--------------+---------+\n"); 
    else
    {
        printf("\n\n\n\n                                      +---------------------------------------+\n");
        printf("                                      | Sorry, This product is out of stock.  |\n");
        printf("                                      +---------------------------------------+\n");
        return 0;
    }
    return 1;
}


int display_camera_inventory(MYSQL* connection)
{
    MYSQL_RES *result_set;
    MYSQL_ROW row;
    int row_count = 0;
    char space[17] = "             ";
    char query[100] = "";

    sprintf(query, "select * from Camera order by id");
    printf("\e[1;1H\e[2J");
    printf("\n\n\n\n");
    if (mysql_query(connection, query))
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
            printf("\n\n\n\n");
            printf("%s+-------------------------------------------------------------------------------------------------------------------+\n",space);
            printf("%s|                                                 PRODUCT - CAMERA                                                  |\n",space);
            printf("%s+--------+------------+-------------+-------------+-----------------+------------+--------------+---------+---------+\n",space);
            printf("%s|  S.No  | BRAND NAME | BRAND MODEL | FORM FACTOR |    SKILL LEVEL  | LENS TYPE  |   EXPOSURE   |  PRICE  |  COUNT  |\n",space);
            printf("%s+--------+------------+-------------+-------------+-----------------+------------+--------------+---------+---------+\n",space);
        }
        printf("%s| %-6s | %-10s | %-11s | %-11s | %-15s | %-10s | %-12s | %-7s | %-7s |\n",space,row[8],row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7]);
        row_count++;
    }
    while(1);

    if(row_count)
         printf("%s+--------+------------+-------------+-------------+-----------------+------------+--------------+---------+---------+\n",space);
    else
    {
        printf("\n\n\n\n                                      +---------------------------------------+\n");
        printf("                                      | Sorry, This product is out of stock.  |\n");
        printf("                                      +---------------------------------------+\n");
        return 0;
    }
    return 1;
}


void input_char(char* arr,int siz)
{
    int  index = 0;
    int  user_input = 0;
    char space[15]="             ";
    memset(arr,'\0',30);
    while((user_input = getchar()) != EOF)
    {
        if(user_input == '\n')
        {
            if(index == 0)
            {
                printf("%sError: entry can't be blank, please re-enter\n",space);
                continue;
            }
            break;
        }
        else if(index != siz + 1)
            arr[index++] = user_input;
    }
}

void input_int(char* arr,int siz)
{
    memset(arr,'\0',30);
    int user_input;
    int index=0;
    char space[15] = "             ";

    while((user_input = getchar()) != EOF)
    {
        if(index == siz)
            break;
        if(user_input == '\n')
        {
            if(!index)
            {
                printf("%sError: entry can't be blank, please re-enter\n",space);
                continue;
            }
            break;
        }
        arr[index++] = user_input;
    }

}
void display_items(MYSQL* connection)
{
    char buff[30] = "";
    char table_name[30]="";
    int  user_input;
    int  index=0;
    //int  choice = 1;
    //int  id;
    char query[300]="";
    char temp_query[300]="";
    char bckp_query[300]="";
    char space[15]="             ";
    //int  count;
    int  ind=0;
    MYSQL_ROW  row;
    MYSQL_RES* result_set;

    while(1)
    {
        memset(buff,'\0',sizeof(buff));
        memset(table_name,'\0',sizeof(table_name));
        index=0;
        //id=0;
        memset(query,'\0',sizeof(query));
        memset(temp_query,'\0',sizeof(temp_query));
        memset(bckp_query,'\0',sizeof(bckp_query));

        printf("\e[1;1H\e[2J");
        printf("\n\n\n\n");
        if(ind)
        {
            printf("\n\n%sError: entered product doesn't exist in the product table\n\n",space);
            ind = 0;
        }
        display_product_list(connection);
        printf("\n\n%sPlease enter the product name from the above displayed list: ",space);

        while((user_input = getchar()) != EOF)
        {
            if(index == 29)
                break;
            if(user_input == '\n')
            {
                if(!index)
                {
                    printf("%sError: product name can't be blank, please re-enter: ",space);
                    continue;
                }
                break;
            }
            buff[index++] = (user_input >= 'A')&&(user_input <= 'Z')?user_input+'a'-'A':user_input;
        }
        if((buff[0] >= 'a')&&(buff[0] <= 'z'))
            buff[0] = buff[0] - 'a' + 'A';
        //printf("Here2\n");
        strcpy(table_name, buff);
        sprintf(query,"select * from products where product_name = '%s'",buff);
        if (mysql_query(connection, query))
        {
            fprintf(stderr, "%s\n", mysql_error(connection));
            mysql_close(connection);
            exit(1);
        }

        result_set = mysql_use_result(connection);

        row = mysql_fetch_row(result_set);

        if(!row)
        {
            ind = 1;
            continue;
        }
        mysql_free_result(result_set);

        if(!strcmp(buff,"Laptop"))
            display_laptop_inventory(connection);
        else if(!strcmp(buff,"Phone"))
            display_phone_inventory(connection);
        else if(!strcmp(buff,"Refrigerator"))
            display_Refrigerator_inventory(connection);
        else if(!strcmp(buff,"Camera"))
            display_camera_inventory(connection);
        else
            display_item_inventory(connection,buff);

        printf("%sWould you like to see more items? Y/N ",space);
        while((user_input = getchar()) != EOF)
        {
            if(user_input == '\n')
            {
                if(!index)
                {
                    printf("\n\n%sError: No valid input has been entered, please try again: ",space);
                    continue;
                }
                break;
            }
            if((user_input == 'Y')||(user_input == 'y'))
            {
                index = 99999999;
            }
            if((user_input == 'N')||(user_input == 'n'))
                index = 9999;
            if((index != 99999999)&&(index != 9999))
                index++;
        }
        if(index == 99999999)
            continue;
        if(index == 9999)
            return;
    }
}
void add_items(MYSQL* connection)
{
    char buff[30] = "";
    char table_name[30]="";
    int  user_input;
    int  index=0;
    int  choice = 1;
    int  id;
    char query[300]="";
    char temp_query[300]="";
    char bckp_query[300]="";
    char space[15]="             ";
    int  count;
    int  ind=0;
    MYSQL_ROW  row;
    MYSQL_RES* result_set;

    while(1)
    {
        memset(buff,'\0',sizeof(buff));
        memset(table_name,'\0',sizeof(table_name));
        index=0;
        id=0;
        memset(query,'\0',sizeof(query));
        memset(temp_query,'\0',sizeof(temp_query));
        memset(bckp_query,'\0',sizeof(bckp_query));
        //printf("Here at top\n");
        printf("\e[1;1H\e[2J");
        printf("\n\n\n\n");
        if(ind)
        {
            printf("\n\n%sError: entered product doesn't exist in the product table\n\n",space);
            ind = 0;
        }
        display_product_list(connection);
        printf("\n\n%sPlease select a product from the above displayed list: ",space);

        while((user_input = getchar()) != EOF)
        {
            if(index == 29)
                break;
            if(user_input == '\n')
            {
                if(!index)
                {
                    printf("%sError: product name can't be blank, please re-enter: ",space);
                    continue;
                }
                break;
            }
            buff[index++] = (user_input >= 'A')&&(user_input <= 'Z')?user_input+'a'-'A':user_input;
        }
        if((buff[0] >= 'a')&&(buff[0] <= 'z'))
            buff[0] = buff[0] - 'a' + 'A';   
        //printf("Here2\n");
        strcpy(table_name, buff);
        sprintf(query,"select * from products where product_name = '%s'",buff);
        if (mysql_query(connection, query))
        {
            //printf("Here3\n");
            fprintf(stderr, "%s\n", mysql_error(connection));
            mysql_close(connection);
            exit(1);
        }

        result_set = mysql_use_result(connection);

        row = mysql_fetch_row(result_set);

        if(!row)
        {
            ind = 1;
            continue;
        }

        memset(query, '\0',sizeof(query));
        mysql_free_result(result_set);

        sprintf(query,"insert into %s values(",buff);
        sprintf(temp_query,"select max(id) from %s",buff);
        if (mysql_query(connection, temp_query))
        {
            //printf("Here1\n");
            fprintf(stderr, "%s\n", mysql_error(connection));
            mysql_close(connection);
            exit(1);
        }
       
        memset(temp_query,'\0',sizeof(temp_query));
        result_set = mysql_use_result(connection);
      
        row = mysql_fetch_row(result_set);
        if(!row[0])
        {
            id = 1;
        }
        else
            id = atoi(row[0]) + 1;

        if(!strcmp(buff,"Laptop"))
        {
            switch (choice)
            {
                case 1:
                {
                    printf("%sPlease enter the brand name: ",space);
                    input_char(buff,9);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                    sprintf(bckp_query,"select count, item_id from %s where brand_name = '%s' and ",table_name,buff);
                }
                case 2:
                {
                    printf("%sPlease enter the processor name: ",space);
                    input_char(buff,9);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                    sprintf(temp_query,"processor_name = '%s' and ",buff);
                    strcat(bckp_query,temp_query);
                }
                case 3:
                {
                    printf("%sPlease enter the processor model: ",space);
                    input_char(buff,9);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                    sprintf(temp_query,"processor_model = '%s' and ",buff);
                    strcat(bckp_query,temp_query);
                }
                case 4:
                {
                    printf("%sPlease enter the operating system: ",space);
                    input_char(buff,9);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                    sprintf(temp_query,"operating_system = '%s' and ",buff);
                    strcat(bckp_query,temp_query);
                }
                case 5:
                {
                    printf("%sPlease enter the RAM size in GB: ",space);
                    input_int(buff,9);
                    sprintf(temp_query,"%d,",atoi(buff));
                    strcat(query,temp_query);
                    sprintf(temp_query,"ram = %d and ",atoi(buff));
                    strcat(bckp_query,temp_query);
                }
                case 6:
                {
                    printf("%sPlease enter the price: ",space);
                    input_int(buff,9);
                    sprintf(temp_query,"%d,",atoi(buff));
                    strcat(query,temp_query);
                }
                case 7:
                {
                    printf("%sPlease enter the hard disk capacity in GB: ",space);
                    input_char(buff,9);
                    sprintf(temp_query,"%d,",atoi(buff));
                    strcat(query,temp_query);
                    sprintf(temp_query,"hard_disk_capacity = %d and ",atoi(buff));
                    strcat(bckp_query,temp_query);
                }
                case 8:
                {
                    printf("%sPlease enter the condition of laptop: ",space);
                    input_int(buff,9);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                    sprintf(temp_query,"condition_of_laptop = '%s'",buff);
                    strcat(bckp_query,temp_query);
                }
                case 9:
                {
                    printf("%sPlease enter the no of pieces for this item: ",space);
                    input_int(buff,9);
                    sprintf(temp_query,"%d,%d,'%s%03d')",count=atoi(buff),id,table_name,id);
                    strcat(query,temp_query);
                    break;
                } 
            }
        }
        else if(!strcmp(buff,"Camera"))
        {
            switch (choice)
            {
                case 1:
                {
                    printf("%sPlease enter the brand name: ",space);
                    input_char(buff,9);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                    sprintf(bckp_query,"select count, item_id from %s where brand_name = '%s' and ",table_name,buff);
                }
                case 2:
                {
                    printf("%sPlease enter the brand model: ",space);
                    input_char(buff,9);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                    sprintf(temp_query,"brand_model = '%s' and ",buff);
                    strcat(bckp_query,temp_query);
                }
                case 3:
                {
                    printf("%sPlease enter the form factor: ",space);
                    input_char(buff,9);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                    sprintf(temp_query,"form_factor = '%s' and ",buff);
                    strcat(bckp_query,temp_query);
                }
                case 4:
                {
                    printf("%sPlease enter the skill level: ",space);
                    input_char(buff,15);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                    sprintf(temp_query,"skill_level = '%s' and ",buff);
                    strcat(bckp_query,temp_query);
                }
                case 5:
                {
                    printf("%sPlease enter the lens type: ",space);
                    input_char(buff,9);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                }
                case 6:
                {
                    printf("%sPlease enter the exposure control: ",space);
                    input_char(buff,9);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                    sprintf(temp_query,"exposure_control = '%s'",buff);
                    strcat(bckp_query,temp_query);
                }
                case 7:
                {
                    printf("%sPlease enter the price: ",space);
                    input_int(buff,9);
                    sprintf(temp_query,"%d,",atoi(buff));
                    strcat(query,temp_query);
                }
                case 8:
                {
                    printf("%sPlease enter the no of pieces for this item: ",space);
                    input_int(buff,9);
                    sprintf(temp_query,"%d,%d,'%s%03d')",count=atoi(buff),id,table_name,id);
                    strcat(query,temp_query);
                    break;
                }
            }
        }
        else if(!strcmp(buff,"Phone"))
        {
            switch (choice)
            {
                case 1:
                {
                    printf("%sPlease enter the brand name: ",space);
                    input_char(buff,9);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                    sprintf(bckp_query,"select count, item_id from %s where brand_name = '%s' and ",table_name,buff);
                }
                case 2:
                {
                    printf("%sPlease enter the brand model: ",space);
                    input_char(buff,9);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                    sprintf(temp_query,"brand_model = '%s' and ",buff);
                    strcat(bckp_query,temp_query);
                }
                case 3:
                {
                    printf("%sPlease enter the processor name: ",space);
                    input_char(buff,15);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                    sprintf(temp_query,"processor = '%s' and ",buff);
                    strcat(bckp_query,temp_query);
                }
                case 4:
                {
                    printf("%sPlease enter the operating system name: ",space);
                    input_char(buff,9);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                    sprintf(temp_query,"operating_system = '%s' and ",buff);
                    strcat(bckp_query,temp_query);
                }
                case 5:
                {
                    printf("%sPlease enter the cellular: ",space);
                    input_char(buff,9);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                }
                case 6:
                {
                    printf("%sPlease enter the colour: ",space);
                    input_char(buff,20);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                }
                case 7:
                {
                    printf("%sPlease enter the wireless carrier: ",space);
                    input_char(buff,20);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                    sprintf(temp_query,"wireless_carrier = '%s'",buff);
                    strcat(bckp_query,temp_query);

                }
                case 8:
                {
                    printf("%sPlease enter the screen size: ",space);
                    input_int(buff,9);
                    sprintf(temp_query,"%d,",atoi(buff));
                    strcat(query,temp_query);
                }
                case 9:
                {
                    printf("%sPlease enter the price: ",space);
                    input_int(buff,9);
                    sprintf(temp_query,"%d,",atoi(buff));
                    strcat(query,temp_query);
                }
                case 10:
                {
                    printf("%sPlease enter the no of pieces for this item: ",space);
                    input_int(buff,9);
                    sprintf(temp_query,"%d,%d,'%s%03d')",count=atoi(buff),id,table_name,id);
                    strcat(query,temp_query);
                    break;
                }

            } 
        }
        else if(!strcmp(buff,"Refrigerator"))
        {
            switch (choice)
            {
                case 1:
                {
                    printf("%sPlease enter the brand name: ",space);
                    input_char(buff,9);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                    sprintf(bckp_query,"select count, item_id from %s where brand_name = '%s' and ",table_name,buff);
                }
                case 2:
                {
                    printf("%sPlease enter the brand model: ",space);
                    input_char(buff,9);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                    sprintf(temp_query,"brand_model = '%s' and ",buff);
                    strcat(bckp_query,temp_query);
                }
                case 3:
                {
                    printf("%sPlease enter the capacity: ",space);
                    input_int(buff,6);
                    sprintf(temp_query,"%d,",atoi(buff));
                    strcat(query,temp_query);
                    sprintf(temp_query,"capacity = %d",atoi(buff));
                    strcat(bckp_query,temp_query);
                }
                case 4:
                {
                    printf("%sPlease enter the no. of doors: ",space);
                    input_int(buff,9);
                    sprintf(temp_query,"%d,",atoi(buff));
                    strcat(query,temp_query);
                }
                case 5:
                {
                    printf("%sPlease enter the price: ",space);
                    input_int(buff,9);
                    sprintf(temp_query,"%d,",atoi(buff));
                    strcat(query,temp_query);
                }
                case 6:
                {
                    printf("%sPlease enter the no of pieces for this item: ",space);
                    input_int(buff,9);
                    sprintf(temp_query,"%d,%d,'%s%03d')",count=atoi(buff),id,table_name,id);
                    strcat(query,temp_query);
                    break;
                }
            }
        }
        else
        {
            switch (choice)
            {
                case 1:
                {
                    printf("%sPlease enter the brand name: ",space);
                    input_char(buff,9);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                    sprintf(bckp_query,"select count, item_id from %s where brand_name = '%s' and ",table_name,buff);
                }
                case 2:
                {
                    printf("%sPlease enter the brand model: ",space);
                    input_char(buff,9);
                    sprintf(temp_query,"'%s',",buff);
                    strcat(query,temp_query);
                    sprintf(temp_query,"brand_model = '%s'",buff);
                    strcat(bckp_query,temp_query);
                }
                case 3:
                {
                    printf("%sPlease enter the price per piece: ",space);
                    input_int(buff,6);
                    sprintf(temp_query,"%d,",atoi(buff));
                    strcat(query,temp_query);
                }
                case 4:
                {
                    printf("%sPlease enter the count of pieces for this item: ",space);
                    input_int(buff,9);
                    sprintf(temp_query,"%d,%d,'%s%03d')",count=atoi(buff),id,table_name,id);
                    strcat(query,temp_query);
                }
            }
        }

        mysql_free_result(result_set);
        
        if (mysql_query(connection, query))
        {
            const char *ptr = mysql_error(connection);

            if(!strncmp(ptr,"Duplicate",9))
            {
                printf("%sRow already exists, updating the count of available pieces\n",space);

                if (mysql_query(connection, bckp_query))
                {
                    fprintf(stderr, "%s\n", mysql_error(connection));
                    mysql_close(connection);
                    exit(1);
                }
                result_set = mysql_store_result(connection);
                row = mysql_fetch_row(result_set);

                count = count + atoi(row[0]);
                memset(query,'\0',sizeof(query));
                sprintf(query,"update %s set count = %d where item_id = '%s'",table_name,count,row[1]);
                if (mysql_query(connection, query))
                {
                    fprintf(stderr, "%s\n", mysql_error(connection));
                    mysql_close(connection);
                    exit(1);
                }
            }
        }
        printf("\n\n%sItem successfully added into %s\n\n",space,table_name);
        printf("%sWould you like to add more items? Y/N ",space);
        while((user_input = getchar()) != EOF)
        {
            if(user_input == '\n')
            {
                if(!index)
                {
                    printf("\n\n%sError: No valid input has been entered, please try again: ",space);
                    continue;
                }
                break;
            }
            if((user_input == 'Y')||(user_input == 'y'))
            {
                index = 99999999;
            }
            if((user_input == 'N')||(user_input == 'n'))
                index = 9999;
            if((index != 99999999)&&(index != 9999))
                index++;
        }
        if(index == 99999999)
            continue;
        if(index == 9999)
            return;
        printf("going above\n");
    }
}

void delete_item(MYSQL *connection)
{
    int   user_input, index;
    char  buff[30]="";
    char  query[300]="";
    char  temp_query[200]="";
    char  space[15] = "             ";
    char  user_count[10]="";
    char  id[10]="";
    int   ind = 0;
    MYSQL_RES *result_set;
    MYSQL_ROW row;

    while(1)
    {
        memset(buff,'\0',sizeof(buff));
        memset(query,'\0',sizeof(query));
        memset(temp_query,'\0',sizeof(temp_query));
        memset(id,'\0',sizeof(id));
        memset(user_count,'\0',sizeof(user_count));
        index = 0;

        printf("\e[1;1H\e[2J");
        printf("\n\n\n\n");
        if(ind)
        {
            printf("\n\n%sError: entered product doesn't exist in the product table\n\n",space);
            ind = 0;
        }
        display_product_list(connection);
        printf("\n\n%sPlease select a product from the above displayed list: ",space);

        while((user_input = getchar()) != EOF)
        {
            if(index == 29)
                break;
            if(user_input == '\n')
            {
                if(!index)
                {
                    printf("%sError: product name can't be blank, please re-enter: ",space);
                    continue;
                }
                break;
            }
            buff[index++] = (user_input >= 'A')&&(user_input <= 'Z')?user_input+'a'-'A':user_input;
        }

        if((buff[0] >= 'a')&&(buff[0] <= 'z'))
            buff[0] = buff[0] - 'a' + 'A';

        sprintf(query,"select * from products where product_name = '%s'",buff);
        if (mysql_query(connection, query))
        {
            fprintf(stderr, "%s\n", mysql_error(connection));
            mysql_close(connection);
            exit(1);
        }

        result_set = mysql_use_result(connection);

        row = mysql_fetch_row(result_set);

        if(!row)
        {
            ind = 1;
            continue;
        }

        memset(query, '\0',sizeof(query));
        mysql_free_result(result_set);
        if(!strcmp(buff,"Laptop"))
        {
            if(!display_laptop_inventory(connection))
            {
                printf("\n\n\n\n%sWould you like to delete items from any other product? Y/N ",space);
                while((user_input = getchar()) != EOF)
                {
                    if(user_input == '\n')
                    {
                        if(!index)
                        {
                            printf("\n\n%sError: No valid input has been entered, please try again: ",space);
                            continue;
                        }
                        break;
                    }
                    if((user_input == 'Y')||(user_input == 'y'))
                    {
                        index = 99999999;
                    }
                    if((user_input == 'N')||(user_input == 'n'))
                        index = 9999;
                    if((index != 99999999)&&(index != 9999))
                        index++;
                }
            }
            if(index == 99999999)
                continue;
            if(index == 9999)
                return;
        }
        else if(!strcmp(buff,"Camera"))
        {

        }
        else if(!strcmp(buff,"Refrigerator"))
        {
            if(!display_Refrigerator_inventory(connection))
            {
                printf("\n\n\n\n%sWould you like to delete items from any other product? Y/N ",space);
                while((user_input = getchar()) != EOF)
                {
                    if(user_input == '\n')
                    {
                        if(!index)
                        {
                            printf("\n\n%sError: No valid input has been entered, please try again: ",space);
                            continue;
                        }
                        break;
                    }
                    if((user_input == 'Y')||(user_input == 'y'))
                    {
                        index = 99999999;
                    }
                    if((user_input == 'N')||(user_input == 'n'))
                        index = 9999;
                    if((index != 99999999)&&(index != 9999))
                        index++;
                }
            }
            if(index == 99999999)
                continue;
            if(index == 9999)
                return;
        }
        else if(!strcmp(buff,"Phone"))
        {

        }
        else
        {
            if(!display_item_inventory(connection, buff))
            {
                printf("\n\n\n\n%sWould you like to delete items from any other product? Y/N ",space);
                while((user_input = getchar()) != EOF)
                {
                    if(user_input == '\n')
                    {
                        if(!index)
                        {
                            printf("\n\n%sError: No valid input has been entered, please try again: ",space);
                            continue;
                        }
                        break;
                    }
                    if((user_input == 'Y')||(user_input == 'y'))
                    {
                        index = 99999999;
                    }
                    if((user_input == 'N')||(user_input == 'n'))
                        index = 9999;
                    if((index != 99999999)&&(index != 9999))
                        index++;
                }
            }
            if(index == 99999999)
                continue;
            if(index == 9999)
                return;
        }
        while(1)
        {
            printf("\n\n%sPlease enter the serial no. of the item from the above displayed list: ",space);

            index=0;

            input_serial_no(id);
            sprintf(query,"select * from %s where item_id = '%s%03d'",buff,buff,atoi(id));

            if (mysql_query(connection, query))
            {
                //printf("Here0\n");
                fprintf(stderr, "%s\n", mysql_error(connection));
                mysql_close(connection);
                exit(1);
            }

            result_set = mysql_use_result(connection);

            row = mysql_fetch_row(result_set);
            if(!row)
            {
                printf("%sError: incorrect serial number entered, please re-enter: ",space);
                input_serial_no(id);
                continue;
            }
            else
                break;
        }

        index = 0;

        sprintf(query,"Delete from %s where item_id = '%s%03d'",buff,buff,atoi(id));
        mysql_free_result(result_set);
        if(mysql_query(connection, query))
        {
            fprintf(stderr, "%s\n", mysql_error(connection));
            mysql_close(connection);
            exit(1);
        }
        printf("\n\n%sItem deleted successfully\n\n",space);
        printf("%sWould you like to delete any other item? Y/N ",space);
        while((user_input = getchar()) != EOF)
        {
            if(user_input == '\n')
            {
                if(!index)
                {
                    printf("\n\n%sError: No valid input has been entered, please try again: ",space);
                    continue;
                }
                break;
            }
            if((user_input == 'Y')||(user_input == 'y'))
            {
                index = 99999999;
            }
            if((user_input == 'N')||(user_input == 'n'))
                index = 9999;
            if((index != 99999999)&&(index != 9999))
                index++;
        }
        if(index == 99999999)
            continue;
        if(index == 9999)
            return;
    }    
}

int display_Refrigerator_inventory(MYSQL* connection)
{
    MYSQL_RES *result_set;
    MYSQL_ROW row;
    int row_count = 0;
    char space[17] = "             ";
    char query[100] = "";

    sprintf(query, "select * from Refrigerator order by id");
    printf("\e[1;1H\e[2J");
    printf("\n\n\n\n");
    if (mysql_query(connection, query))
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
            printf("\n\n\n\n");
            printf("%s+-------------------------------------------------------------------------------+\n",space);
            printf("%s|                            PRODUCT REFRIGERATOR                               |\n",space);
            printf("%s+--------+------------+-------------+----------+-------+------------+-----------+\n",space);
            printf("%s|  S.No  | BRAND NAME | BRAND MODEL | CAPACITY | DOORS |   PRICE    |   COUNT   |\n",space);
            printf("%s+--------+------------+-------------+----------+-------+------------+-----------+\n",space);
        }
         printf("%s| %-6s | %-10s | %-11s | %-8s | %-5s | %-10s | %-9s |\n",space,row[6],row[0],row[1],row[2],row[3],row[4],row[5]);
        row_count++;
    }
    while(1);

    if(row_count)
         printf("%s+--------+------------+-------------+----------+-------+------------+-----------+\n",space);
    else
    {
        printf("\n\n\n\n                                      +---------------------------------------+\n");
        printf("                                      | Sorry, This product is out of stock.  |\n");
        printf("                                      +---------------------------------------+\n");
        return 0;
    }
    return 1;
}

int display_laptop_inventory(MYSQL *connection)
{
    MYSQL_RES *result_set;
    MYSQL_ROW row;
    int row_count = 0;
    char query[100] = "";

    sprintf(query, "select * from Laptop order by id");

    printf("\e[1;1H\e[2J");
    printf("\n\n\n\n");
    if (mysql_query(connection, query))
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
            printf("\n\n\n\n");
                        printf(" +------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
            printf(" |                                                                PRODUCT LAPTOP                                                                        |\n");
            printf(" +------+------------+----------------+-----------------+------------------+------------+------------+--------------------+---------------------+-------+\n");
            printf(" | S.No | brand_name | processor_name | processor_model | operating_system |    ram     |   price    | hard_disk_capacity | condition_of_laptop | count |\n");
            printf(" +------+------------+----------------+-----------------+------------------+------------+------------+--------------------+---------------------+-------+\n");

        }
        printf(" | %4s | %-10s |   %-10s   |   %-10s    |    %-10s    | %-10s | %-10s |        %5s       |     %-10s      | %5s |\n",row[9],row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8]);
        row_count++;
    }
    while(1);

    if(row_count)
        printf(" +------+------------+----------------+-----------------+------------------+------------+------------+--------------------+---------------------+-------+\n");

    else
    {
        printf("\n\n\n\n                                      +---------------------------------------+\n");
        printf("                                      | Sorry, This product is out of stock.  |\n");
        printf("                                      +---------------------------------------+\n");
        return 0;
    }
    return 1;
}


int display_item_inventory(MYSQL* connection, char *product_name)
{
    MYSQL_RES *result_set;
    MYSQL_ROW row;
    int row_count = 0;
    char space[17] = "             ";
    char query[100] = "";

    sprintf(query, "select * from %s order by id",product_name);
    printf("\e[1;1H\e[2J");
    printf("\n\n\n\n");
    if (mysql_query(connection, query))
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
            printf("\n\n\n\n");
            printf("%s+-------------------------------------------------------------------+\n",space);
            printf("%s|                      PRODUCT %-30s       |\n",space,product_name); 
            printf("%s+--------+------------+-------------+------------+------------------+\n",space); 
            printf("%s|  S.No  | BRAND NAME | BRAND MODEL |   PRICE    | AVAILABLE PIECES |\n",space);
            printf("%s+--------+------------+-------------+------------+------------------+\n",space);
        }
        printf("%s| %-6s | %-10s | %-11s | %-10s | %-16s |\n",space,row[4],row[0],row[1],row[2],row[3]);
        row_count++;
    }
    while(1);

    if(row_count)
        printf("%s+--------+------------+-------------+------------+------------------+\n",space);
    else
    {
        printf("\n\n\n\n                                      +---------------------------------------+\n");
        printf("                                      | Sorry, This product is out of stock.  |\n");
        printf("                                      +---------------------------------------+\n");
        return 0;
    } 
    return 1;
}

