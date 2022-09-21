#include<stdio.h>
#include<mysql.h>

extern void add_to_cart(MYSQL*);
extern void bill_to_file(MYSQL*);

void show_cart(MYSQL *conn)
{
    MYSQL_RES *result_set;
    MYSQL_ROW row;
    int row_count = 0;
    char space[17] = "             ";
    char query[100] = "";
    int user_input;
    int index;

        index = 0;
        sprintf(query, "select * from cart");
        printf("\e[1;1H\e[2J");
        printf("\n\n\n\n");

        if (mysql_query(conn, query))
        {
            fprintf(stderr, "%s\n", mysql_error(conn));
            mysql_close(conn);
            exit(1);
        }

        result_set = mysql_use_result(conn);
    
        do
        {
            row = mysql_fetch_row(result_set);

            if(!row)
                break;
            else if(row_count == 0)
            {
                printf("\n\n\n\n");
                printf("%s+-------------------------------------------------------------------------+\n",space);
                printf("%s|                            SHOPPING CART                                |\n",space);
                printf("%s+--------------+------------+---------------------------+---------+-------+\n",space); 
                printf("%s| PRODUCT NAME | BRAND NAME |           MODEL           |  PRICE  | COUNT |\n",space);
                printf("%s+--------------+------------+---------------------------+---------+-------+\n",space);
            }
            printf("%s| %-12s | %-10s | %-25s | %-7s | %-5s |\n",space,row[0],row[1],row[2],row[3],row[4]);
            row_count++;
        }
        while(1);

        if(row_count)
            printf("%s+--------------+------------+---------------------------+---------+-------+\n",space);
        else    
        {
            printf("\n\n\n\n                                      +--------------------------------------+\n");
            printf("                                      |      Sorry, cart is empty now!       |\n");
            printf("                                      +--------------------------------------+\n");
        }

        printf("%sWould you like to add items to your cart? Y/N: ",space);
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
        mysql_free_result(result_set);
        if(index == 99999999)
            add_to_cart(conn);
        sprintf(query, "select * from cart");

        if (mysql_query(conn, query))
        {
            fprintf(stderr, "%s\n", mysql_error(conn));
            mysql_close(conn);
            exit(1);
        }
        result_set = mysql_store_result(conn);
        index=0;
        if(mysql_num_rows(result_set))
        {
            printf("\n%sWould you like to finalize your purchase? Y/N: ",space);
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
            mysql_free_result(result_set);
            if(index == 99999999)
            {
                bill_to_file(conn);
                printf("\n\n%sBill has been generated, Thanks for shopping!",space);
            }
        
        }
    printf("\n\n\n\n             Enter any key to go back to the previous menu: ");
    while((user_input = getchar()) != EOF)
    {
        if(user_input == '\n')
            break;
    }
}

