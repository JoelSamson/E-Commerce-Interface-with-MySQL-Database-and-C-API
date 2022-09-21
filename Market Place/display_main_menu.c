#include<stdio.h>
#include<stdlib.h>

extern void display_admin_sub_menu(void);
extern void database_connect(int);
extern void search_sub_menu();

void display_main_menu(void)
{
    int input, eligible_input;

    do
	{	
		printf("\e[1;1H\e[2J");
		printf("\n\n\n\n                                                               MAIN MENU\n");
        printf("             1) Admin\n");
        printf("             2) Search for products\n");
        printf("             3) My shopping cart\n");
        printf("             4) Quit\n\n");
        printf("\n\n             Please choose any option: ");

		while((input = getchar()) != EOF)
		{
			if(input == '\n')
				break;
			else
				eligible_input = input;
		}        

		switch(eligible_input-'0')
		{
			case 1:
			{
				display_admin_sub_menu();
				break;
			}
            case 2:
            {
                search_sub_menu();
                break;
            }
            case 3:
            {
                //printf("Here in main");
                database_connect(7);
                break;
            }
            case 4:
            {
                database_connect(8);
                exit(0);
            }
        }
    }
    while(1);
}
