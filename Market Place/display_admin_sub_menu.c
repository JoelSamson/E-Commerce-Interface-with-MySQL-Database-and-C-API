#include<stdio.h>

extern void display_admin_delete_sub_menu(void);
extern void display_admin_insert_sub_menu(void);
extern void admin_display_sub_menu(void);

void  display_admin_sub_menu(void)
{
    int input, eligible_input;

    do
    {
        printf("\e[1;1H\e[2J");
        printf("\n\n\n\n                                                               SUB MENU - ADMIN\n");
        printf("             1) Insert product info\n");
        printf("             2) Delete product info\n");
        printf("             3) Display list of products\n");
        printf("             4) Go back to the previous menu\n\n");
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
                display_admin_insert_sub_menu();
                break;
            }
            case 2:
            {
                display_admin_delete_sub_menu();
                break;
            }
            case 3:
            {
                admin_display_sub_menu();
                break;
            }
            case 4:
            {
                return;
            }
        } 
    }
    while(1);
    eligible_input = -2;
}
