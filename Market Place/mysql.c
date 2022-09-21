#include<stdio.h>
#include<stdlib.h>
#include<mysql.h>
#include<string.h>
#include<unistd.h>

extern void  create_product_table(MYSQL*, char*);
extern void  display_product_list(MYSQL*);
extern char* add_product(MYSQL*);
extern void  delete_product(MYSQL*);
extern void  display_items(MYSQL*);
extern void  add_to_cart(MYSQL*);
extern void  clear_cart(MYSQL*);
extern void  bill_to_file(MYSQL*);
extern void  delete_item(MYSQL*);
extern void  add_items(MYSQL*);
extern void  display_items(MYSQL*);
extern void  show_cart(MYSQL*);

void database_connect(int option) 
{
	MYSQL *connection;
	
	char *server = "helios.vse.gmu.edu";
	char *user = "jsamson6";
	char *password = "";
	char *database = "jsamson6";
	
	connection = mysql_init(NULL);
	
	if (!mysql_real_connect(connection, server, user, password, database, 0, NULL, 0)) 
    {
		fprintf(stderr, "%s\n", mysql_error(connection));
		exit(1);
	}
    switch (option) 
    {
        case 1:
        {
            create_product_table(connection,add_product(connection));
            break;
        }
        case 2:
        {
            add_items(connection);
            //display_product_laptop_inventory(connection);
            //add_product(connection);
            break;
        }
        case 3:
        {
            delete_product(connection);//to delete the product from products table and drop that product's table
            break;
        }
        case 4:
        {
            delete_item(connection);
            break;
        }
        case 5:
        {
            printf("\e[1;1H\e[2J");
            printf("\n\n\n\n");
            display_product_list(connection);
            int user_input;
            printf("\n\n\n\n             Enter any key to go back to the previous menu: ");
            while((user_input = getchar()) != EOF)
            {
                if(user_input == '\n')
                break;
            }
            break;
        }
        case 6:
        {
            display_items(connection);    
            break;
        }
        case 7:
        {
            show_cart(connection);
            break;
        }
        case 8:
        {
            clear_cart(connection);
        }
    }
}
