#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<mysql.h>

extern void display_product_list(MYSQL*);
extern int  display_laptop_inventory(MYSQL *);
extern int  display_item_inventory(MYSQL*, char*);
extern int  display_Refrigerator_inventory(MYSQL*);
extern int  display_camera_inventory(MYSQL*);
extern int  display_phone_inventory(MYSQL*);

void input_serial_no(char* id)
{
    memset(id,'\0',10);
    int user_input;
    int index=0;
    char space[15] = "             ";

    while((user_input = getchar()) != EOF)
    {
        if(index == 29)
            break;

        if(user_input == '\n')
        {
            if(!index)
            {
                printf("%sError: product name can't be blank, please re-enter\n",space);
                continue;
            }
            break;
        }
        id[index++] = user_input;
    }

}

void take_user_count(char *user_count, int size)
{
    char space[15] = "             ";  
    int  index = 0;
    int  user_input;

    memset(user_count,'\0',size);

    printf("%sPlease enter the count of item you want to add to the cart: ",space);

    while((user_input = getchar()) != EOF)
    {
        if(index == 9)
            break;
        if(user_input == '\n')
        {
            if(!index)
            {
                printf("%sError: product count can't be blank, please re-enter: ",space);
                continue;
            }
            break;
        }
        if(!((user_input >= '0')&&(user_input <= '9')))
        {
            printf("%sError: wrong data entered, please re-enter digits between 0-9: ",space);
            memset(user_count, '\0', size);
            index=0;
            continue;
        }
        user_count[index++] = user_input;
    }
}

void add_to_cart(MYSQL* connection)
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
                printf("\n\n\n\n%sWould you like to buy any other product? Y/N ",space);
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
            if(!display_camera_inventory(connection))
            {
                printf("\n\n\n\n%sWould you like to buy any other product? Y/N ",space);
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
        else if(!strcmp(buff,"Refrigerator"))
        {
            if(!display_Refrigerator_inventory(connection))
            {
                printf("\n\n\n\n%sWould you like to buy any other product? Y/N ",space);       
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
            if(!display_phone_inventory(connection))
            {
                printf("\n\n\n\n%sWould you like to buy any other product? Y/N ",space);
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
        else
        {
            if(!display_item_inventory(connection, buff))
            {
                printf("\n\n\n\n%sWould you like to buy any other product? Y/N ",space);
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
        take_user_count(user_count,sizeof(user_count));

        index = 0;

        while(1)
        {
            if(index == 0)
            {
                sprintf(query,"Insert into cart values('%s','%s',",buff,row[index]);
            }
            if(index == 1)
            {
                sprintf(temp_query,"'%s",row[index]);
                strcat(query,temp_query);
            }
            if(((strcmp(buff,"Refrigerator"))&&(strcmp(buff,"Laptop"))&&(strcmp(buff,"Camera"))&&(strcmp(buff,"Phone")))&&(index > 1))
            {
                while(atoi(row[3]) < atoi(user_count))
                {
                    printf("\e[1;1H\e[2J");
                    printf("\n\n\n\n");
                    if(atoi(row[3]))
                    {
                        printf("%sOnly %s pieces are available for the chosen item, you've entered %s\n\n\n\n",space,row[3],user_count);
                        take_user_count(user_count,sizeof(user_count));
                    }
                    else
                    {
                        ind = 1;
                        printf("\n\n");
                        printf("%s+-----------------------------------------+\n",space);
                        printf("%s|  Currently this item is our of stock    |\n",space);
                        printf("%s+-----------------------------------------+\n",space);
                        break;
                    }
                }
                sprintf(temp_query,"',%d,%d,'%s%03d')",atoi(row[2]),atoi(user_count),buff,atoi(id));
                strcat(query,temp_query);
                break;
            }
            if((!strcmp(buff,"Refrigerator"))&&(index > 1))
            {
                while(atoi(row[5]) < atoi(user_count))
                {
                    printf("\e[1;1H\e[2J");
                    printf("\n\n\n\n");
                    if(atoi(row[5]))
                    {
                        printf("%sOnly %s pieces are available for the chosen item, you've entered %s \n\n\n\n",space,row[5],user_count);
                        take_user_count(user_count,sizeof(user_count));
                    }
                    else
                    {
                        ind = 1;
                        printf("\n\n");
                        printf("%s+-----------------------------------------+\n",space);
                        printf("%s|  Currently this item is our of stock    |\n",space);
                        printf("%s+-----------------------------------------+\n",space);
                        break;
                    }

                }
                sprintf(temp_query,"',%d,%d,'%s%03d')",atoi(row[4]),atoi(user_count),buff,atoi(id));
                strcat(query,temp_query);
                break;
            }
            if((!strcmp(buff,"Laptop"))&&(index > 1))
            {
                while(atoi(row[8]) < atoi(user_count))
                {
                    printf("\e[1;1H\e[2J");
                    printf("\n\n\n\n");
                    if(atoi(row[8]))
                    {
                        printf("%sOnly %s pieces are available for the chosen item, you've entered %s\n\n\n\n",space,row[8],user_count);
                        take_user_count(user_count,sizeof(user_count));
                    }
                    else
                    {
                        ind = 1;
                        printf("\n\n");
                        printf("%s+-----------------------------------------+\n",space);
                        printf("%s|  Currently this item is our of stock    |\n",space);
                        printf("%s+-----------------------------------------+\n",space);
                        break;
                    }

                }
                sprintf(temp_query,"-%s',%d,%d,'%s%03d')",row[2],atoi(row[5]),atoi(user_count),buff,atoi(id));
                strcat(query,temp_query);
                break;
            }
            if((!strcmp(buff,"Camera"))&&(index > 1))
            {
                while(atoi(row[7]) < atoi(user_count))
                {
                    printf("\e[1;1H\e[2J");
                    printf("\n\n\n\n");
                    if(atoi(row[7]))   
                    { 
                        printf("%sOnly %s pieces are available for the chosen item, you've entered %s\n\n\n\n",space,row[7],user_count);
                        take_user_count(user_count,sizeof(user_count));
                    }
                    else
                    {
                        ind = 1;
                        printf("\n\n");
                        printf("%s+-----------------------------------------+\n",space);
                        printf("%s|  Currently this item is our of stock    |\n",space);
                        printf("%s+-----------------------------------------+\n",space);
                        break;
                    }
                }
                sprintf(temp_query,"',%d,%d,'%s%03d')",atoi(row[6]),atoi(user_count),buff,atoi(id));
                strcat(query,temp_query);
                break;
            }
            if((!strcmp(buff,"Phone"))&&(index > 1))
            {
                while(atoi(row[9]) < atoi(user_count))
                {
                    printf("\e[1;1H\e[2J");
                    printf("\n\n\n\n");
                    if(atoi(row[9]))
                    {
                        printf("%sOnly %s pieces are available for the chosen item, you've entered %s\n\n\n\n",space,row[9],user_count);
                        take_user_count(user_count,sizeof(user_count));
                    }
                    else
                    {
                        ind = 1;
                        printf("\n\n");
                        printf("%s+-----------------------------------------+\n",space);
                        printf("%s|  Currently this item is our of stock    |\n",space);
                        printf("%s+-----------------------------------------+\n",space);
                        break;
                    }
                }
                sprintf(temp_query,"',%d,%d,'%s%03d')",atoi(row[8]),atoi(user_count),buff,atoi(id));
                strcat(query,temp_query);
                break;
            }
            index++;
        }  
        mysql_free_result(result_set);

        if(ind)
        {
            index = 0;
                printf("\n\n\n\n%sWould you like to buy any other product? Y/N ",space);
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
            {
                ind =0;
                continue;
            }
            if(index == 9999)
                return;
        
            
        if (mysql_query(connection, query))
        {
            fprintf(stderr, "%s\n", mysql_error(connection));
            mysql_close(connection);
            exit(1);
        } 
        printf("\n\n%sItem successfully added to your cart\n\n",space);
        printf("%sWould you like to buy any other product? Y/N ",space);
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
        mysql_free_result(result_set);
    }

}
