#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql.h>

void display_product_list(MYSQL*);

void delete_product(MYSQL *connection) //to delete the product from product table and drop that product's table
{
    char product_name[50] ="";
    int  user_input;
    int  index = 0;
    char space[17] = "             ";
    char query[200] = "";

    MYSQL_RES *result_set;

    printf("\e[1;1H\e[2J");
    printf("\n\n");
    display_product_list(connection);
    printf("\n\n\n\n\n%sPlease enter the name of the product from above product list to be deleted: ",space);

    while((user_input = getchar()) != EOF)
    {
        if(index == 49)
            break;
        if(user_input == '\n')
            break;
        else
            product_name[index++] = user_input;
    }

    sprintf(query, "select * from products where product_name = '%s'",product_name);

    if (mysql_query(connection, query))
    {
        fprintf(stderr, "%s\n", mysql_error(connection));
        mysql_close(connection);
        exit(1);
    }

    result_set = mysql_store_result(connection);

    if(mysql_num_rows(result_set))
    {
        memset(query,'\0',sizeof(query));
        if(product_name[0] >= 'a')
            product_name[0] = product_name[0] - 'a' + 'A';  //Upper casing the 1st character

        sprintf(query,"delete from products where product_name = '%s'",product_name);

        if (mysql_query(connection, query))
        {
            fprintf(stderr, "%s\n", mysql_error(connection));
            mysql_close(connection);
            exit(1);
        }
        printf("\e[1;1H\e[2J");
        printf("\n\n");

        printf("\n\n%sCurrent list of products after deleting product <%s>:\n\n\n",space,product_name);

        sprintf(query,"Drop table %s",product_name);

        if (mysql_query(connection, query))
        {
            fprintf(stderr, "%s\n", mysql_error(connection));
            mysql_close(connection);
            exit(1);
        }

    }
    else
        printf("%sProduct \"%s\" doesn't exist in the list of products:\n\n\n",space,product_name);

    display_product_list(connection);

    printf("\n\n\n\n             Enter any key to go back to the menu: ");
    while((user_input = getchar()) != EOF)
    {
        if(user_input == '\n')
            break;
    }
}


void display_product_list(MYSQL *connection)
{
    MYSQL_RES *result_set;
    MYSQL_ROW row;
    int row_count = 0;
    char space[17] = "             ";
    char query[100] = "";

    sprintf(query, "select * from products order by product_id");

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
            printf("\n\n\n\n%s+------------+--------------------------------+\n",space); //column names to be printed only once (before any row data is printed)
            printf("%s| PRODUCT ID |      PRODUCT NAME              |\n",space);
            printf("%s+------------+--------------------------------+\n",space);
        }
        printf("%s| %-10s | %-30s |\n",space,row[0],row[1]);
        row_count++;
    }
    while(1);

    if(row_count)
        printf("%s+------------+--------------------------------+\n",space);
    else
    {
        printf("\n\n\n\n                                      +--------------------------------------+\n");
        printf("                                      | 0 rows fetched from \"PRODUCTS\" table |\n");
        printf("                                      +--------------------------------------+\n");
    }
}


char* add_product(MYSQL *connection)
{
    char *product_name = malloc(30);
    int  user_input;
    int  index = 0;
    char space[17] = "             ";
    char query[200] = "";


    MYSQL_RES *result_set;

    printf("\e[1;1H\e[2J");
    printf("\n\n");
    memset(product_name,'\0',30);
    printf("\n\n\n\n\n%sPlease enter the name of the product to be entered: ",space);

    while((user_input = getchar()) != EOF)
    {
        if(index == 29)
            break;
        if(user_input == '\n')
        {
            if(index == 0)
            {
                printf("%sError: product name cannot be blank, please re-enter: ",space);
                continue;
            }
            break;
        }
        else
            product_name[index++] = user_input;
    }

    sprintf(query, "select * from products where product_name = '%s'",product_name);

    if (mysql_query(connection, query))
    {
        fprintf(stderr, "%s\n", mysql_error(connection));
        mysql_close(connection);
        memset(product_name,'\0',30);
        product_name = NULL;
        exit(1);
    }

    result_set = mysql_store_result(connection);

    if(!mysql_num_rows(result_set))
    {
        memset(query,'\0',sizeof(query));
        if(product_name[0] >= 'a')
            product_name[0] = product_name[0] - 'a' + 'A';  //Upper casing the 1st character

        sprintf(query,"insert into products (product_name) values(\"%s\")",product_name);

        if (mysql_query(connection, query))
        {
            fprintf(stderr, "%s\n", mysql_error(connection));
            memset(product_name,'\0',30);
            product_name = NULL;
            mysql_close(connection);
            exit(1);
        }

        printf("\n\n%sCurrent list of products after adding product <%s>:\n\n\n",space,product_name);
    }
    else
    {
        printf("%sProduct \"%s\" already exists in the list of products:\n\n\n",space,product_name);
        memset(product_name,'\n',30);
    }
    display_product_list(connection);
    printf("\n\n\n\n             Enter any key to go back to the menu: ");
    while((user_input = getchar()) != EOF)
    {
        if(user_input == '\n')
            break;
    }

    return product_name;
}

void create_product_table(MYSQL *connection, char *product_name)
{
    char query[300] = "";
    if(product_name[0]=='\0')
        return;
    sprintf(query, "create table %s(brand_name varchar(10),brand_model varchar(10),price decimal(10,2) default 0, count int default 0,id int,item_id varchar(15), primary key(brand_name,brand_model))",product_name);

    if (mysql_query(connection, query))
    {
        fprintf(stderr, "%s\n", mysql_error(connection));
        mysql_close(connection);
        exit(1);
    }
    printf("Table for product \"%s\" created\n",product_name); 
}
