#include<stdio.h>
#include<mysql.h>

void clear_cart(MYSQL *connection)
{
    if (mysql_query(connection, "delete from cart"))
    {
        fprintf(stderr, "%s\n", mysql_error(connection));
        mysql_close(connection);
        exit(1);
    }
}
