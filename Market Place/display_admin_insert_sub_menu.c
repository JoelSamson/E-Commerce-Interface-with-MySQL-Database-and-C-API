#include<stdio.h>

extern void database_connect(int);

void display_admin_insert_sub_menu(void)
{
    int input, eligible_input;

    do
    {
        printf("\e[1;1H\e[2J");
        printf("\n\n\n\n                                                               DELETE \n");
        printf("             1) Add product\n");
        printf("             2) Insert product item(s)\n");
        printf("             3) Go back to the previous menu\n\n");
        printf("\n\n             Please enter an option: ");

        while((input = getchar()) != EOF)
        {
            if(input == '\n')
            {
                break;
            }
            else
            {
                eligible_input = input;
            }
        }

        switch(eligible_input-'0')
        {
            case 1:
            {
                database_connect(1);
                break;
            }
            case 2:
            {
                database_connect(2); 
                break;
            }
            case 3:
            {
                return;
            }
        }
    }
    while(1);
}

