#include<stdio.h>

void database_connect(int);

void admin_display_sub_menu(void)
{
    int input, eligible_input;

    do
    {
        printf("\e[1;1H\e[2J");
        printf("\n\n\n\n                                                               SUB MENU - ADMIN\n");
        printf("             1) Display products\n");
        printf("             2) Display product Details\n");
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
                database_connect(5);
                break;
            }
            case 2:
            {
                database_connect(6);
                break;
            }
            case 3:
            {
                return;
            }
        }
    }
    while(1);
    eligible_input = -2;
}

