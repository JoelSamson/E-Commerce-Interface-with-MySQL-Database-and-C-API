#include<stdio.h>

extern void database_connect(int);

void display_admin_delete_sub_menu(void)
{
    int input, eligible_input;

    do
    {
        printf("\e[1;1H\e[2J");
        printf("\n\n\n\n                                                               DELETE \n");
        printf("             1) Delete product info\n");
        printf("             2) Delete product item\n");
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
                database_connect(3);
                break;
            }
            case 2:
            {
                database_connect(4);
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

