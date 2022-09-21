#include<stdio.h>
#include<stdlib.h>
#include<mysql.h>
#include<string.h>

extern void display_product_list(MYSQL *);
extern int  display_laptop_inventory(MYSQL *);
extern int  display_item_inventory(MYSQL*, char*);
extern int  display_Refrigerator_inventory(MYSQL*);
extern int  display_camera_inventory(MYSQL*);
extern int  display_phone_inventory(MYSQL*);

void userInput(char *);
void userInput(char *buff)
{
	int user_input;
	int index=0;

	while((user_input = getchar()) != EOF)
	{
		if(index == 49)
		break;
        if(user_input == '\n')
        {
		break;
        }
        else
            buff[index++] = user_input;
    }
}

void laptop(MYSQL *conn);
void Camera(MYSQL *conn);
void phone(MYSQL *conn);
void refrigerator(MYSQL *conn);

void laptop(MYSQL *conn)
{
	system("clear");
			printf("\n\n\n\n");

			printf("                                                   Searching for Laptop\n");
                        printf("\n\n");
			MYSQL_RES *result_set;
			MYSQL_ROW row;
			MYSQL_ROW row1;
			int row_count = 0;
			char space[17] = "             ";
			char query[600] = "";
			char temp_query[200];




			char b[50]="";
			char c[50]="";
            char o[50]="";
            char p[50]="";


			int a=1;
			if(a==1)
			{
				sprintf(query, "select distinct brand_name from Laptop");
				if (mysql_query(conn, query))
				{
					fprintf(stderr, "%s\n", mysql_error(conn));
					mysql_close(conn);
					exit(1);
				}
				result_set=mysql_use_result(conn);
				do{
					row = mysql_fetch_row(result_set);
					if(!row)
						break;
					else if(row_count==0)
					{
                            printf("\n%s  +------------------------------+\n",space);
							printf("%s  |        AVAILABLE BRANDS      |--->",space);
				    }
					printf(" %s,",row[0]);
					row_count++;
				}while(1);

				mysql_free_result(result_set);

				sprintf(query, "select distinct condition_of_laptop from Laptop");
				if (mysql_query(conn, query))
				{
					fprintf(stderr, "%s\n", mysql_error(conn));
					mysql_close(conn);
					exit(1);
				}
				result_set=mysql_use_result(conn);


				row_count=0;

				do{
					row1 = mysql_fetch_row(result_set);
					if(!row1)
						break;
					else if(row_count==0)
						{
                            printf("\n%s  +------------------------------+\n",space);
                            printf("%s  |    AVAILABLE CONDITIONS      |--->",space);
						}
					printf(" %s,",row1[0]);
					row_count++;
				}while(1);

				mysql_free_result(result_set);

				sprintf(query, "select distinct operating_system from Laptop");
				if (mysql_query(conn, query))
				{
					fprintf(stderr, "%s\n", mysql_error(conn));
					mysql_close(conn);
					exit(1);
				}
				result_set=mysql_use_result(conn);


				row_count=0;

				do{
					row1 = mysql_fetch_row(result_set);
					if(!row1)
						break;
					else if(row_count==0)
						{
							printf("\n%s  +------------------------------+\n",space);
							printf("%s  | AVAILABLE OPERATING SYSTEMS  |--->",space);
						}
					printf(" %s,",row1[0]);
					row_count++;

				}while(1);

				mysql_free_result(result_set);

				sprintf(query, "select distinct processor_model from Laptop");
				if (mysql_query(conn, query))
				{
					fprintf(stderr, "%s\n", mysql_error(conn));
					mysql_close(conn);
					exit(1);
				}
				result_set=mysql_use_result(conn);


				row_count=0;

				do
				{
					row1 = mysql_fetch_row(result_set);
					if(!row1)
						break;
					else if(row_count==0)
					{
						printf("\n%s  +------------------------------+\n",space);
                        printf("%s  |  AVAILABLE PROCESSOR MODELS  |--->",space);


					}
					printf(" %s,",row1[0]);
					row_count++;
				}while(1);

				if(row_count)
				    printf("\n%s  +------------------------------+\n",space);
				mysql_free_result(result_set);


			}


			sprintf(query, "select * from Laptop where (1 = 1)");
			printf("\n\n");
			printf("             Enter the brand (Enter None if not required): ");
            userInput(b);
            if(b[0] != '\0')
            {
                sprintf(temp_query," and brand_name = '%s'",b);
                strcat(query,temp_query);
            }
            printf("\n\n");

			printf("             Enter the Condition (Enter None if not required): ");
			userInput(c);
            if(c[0] != '\0')
            {
                sprintf(temp_query," and condition_of_laptop = '%s'",c);
                strcat(query,temp_query);
            }
			printf("\n\n");

			printf("             Enter the Operating System (Enter None if not required): ");
			userInput(o);
            if(o[0] != '\0')
            {
                sprintf(temp_query," and operating_system = '%s'",o);
                strcat(query,temp_query);
            }
			printf("\n\n");

			printf("             Enter the Processor model (Enter None if not required): ");
			userInput(p);
            if(p[0] != '\0')
            {
                sprintf(temp_query," and processor_model = '%s'",p);
                strcat(query,temp_query);
            }
			printf("\n\n");


			y:

			printf("%sPlease Enter A/a for Ascending order by price or D/d for Descending: ",space);
			char z;
			scanf(" %c",&z);
			getchar();

			if(z=='D'||z=='d')
			{
				sprintf(temp_query, " order by price desc");
                strcat(query,temp_query);
			}
            else if(z == 'A' || z== 'a')
			{
				sprintf(temp_query, " order by price");
                strcat(query,temp_query);
			}
			else
			{
				printf("Please enter a correct option\n");
				goto y;
			}
            printf("QUERY -> %s\n",query);
            if (mysql_query(conn, query))
            {
                fprintf(stderr, "%s\n", mysql_error(conn));
                mysql_close(conn);
                exit(1);
            }
			result_set = mysql_use_result(conn);


			system("clear");
			row_count=0;

		do
			{
				row = mysql_fetch_row(result_set);
				if(!row)
					break;
				else if(row_count==0)
				{
					printf("\n\n\n\n");
                    printf(" +------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
            		printf(" |                                                                PRODUCT LAPTOP                                                                        |\n");
            	printf(" +------+------------+----------------+-----------------+------------------+------------+------------+--------------------+---------------------+-------+\n");
            	printf(" | S.No | brand_name | processor_name | processor_model | operating_system |    ram     |   price    | hard_disk_capacity | condition_of_laptop | count |\n");
            	printf(" +------+------------+----------------+-----------------+------------------+------------+------------+--------------------+---------------------+-------+\n");

				}
				printf(" | %4s | %-10s |   %-10s   |   %-10s    |    %-10s    | %-10s | %-10s |        %5s       |     %-10s      | %5s |\n",row[9],row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8]);


				row_count++;
			}while(1);
			if(row_count)
				printf(" +------+------------+----------------+-----------------+------------------+------------+------------+--------------------+---------------------+-------+\n");
			else
			{
			printf("\n\n\n\n                                      +---------------------------------------+\n");
        	printf("                                      | Sorry, This product does'nt exist.    |\n");
        	printf("                                      +---------------------------------------+\n");
			}
}



void Camera(MYSQL *conn)
{
	system("clear");
			printf("\n\n\n\n");

			printf("                                           Searching for Camera\n");
                        printf("\n\n");
			MYSQL_RES *result_set;
			MYSQL_ROW row;
			//MYSQL_ROW row1;
			int row_count = 0;
			char space[17] = "             ";
			char query[600] = "";

			char b[50]="";
			char c[50]="";
            char o[50]="";
            char p[50]="";


			int a=1;
			if(a==1)
			{
				sprintf(query, "select distinct brand_name from Camera");
				if (mysql_query(conn, query))
				{
					fprintf(stderr, "%s\n", mysql_error(conn));
					mysql_close(conn);
					exit(1);
				}
				result_set=mysql_use_result(conn);
				do{
					row = mysql_fetch_row(result_set);
					if(!row)
						break;
					else if(row_count==0)
						{
							printf("\n%s  +------------------------------+\n",space);
                            printf("%s  |        AVAILABLE BRANDS      |--->",space);
						}
					printf(" %s,",row[0]);

					row_count++;
				}while(1);

				mysql_free_result(result_set);


				sprintf(query, "select distinct form_factor from Camera");
				if (mysql_query(conn, query))
				{
					fprintf(stderr, "%s\n", mysql_error(conn));
					mysql_close(conn);
					exit(1);
				}
				result_set=mysql_use_result(conn);


				row_count=0;

				do{
					row = mysql_fetch_row(result_set);
					if(!row)
						break;
					else if(row_count==0)
						{
						    printf("\n%s  +------------------------------+\n",space);
                            printf("%s  |    AVAILABLE FORM FACTOR     |--->",space);
						}
					printf(" %s,",row[0]);
					row_count++;
				}while(1);


				mysql_free_result(result_set);

				sprintf(query, "select distinct skill_level from Camera");
				if (mysql_query(conn, query))
				{
					fprintf(stderr, "%s\n", mysql_error(conn));
					mysql_close(conn);
					exit(1);
				}
				result_set=mysql_use_result(conn);


				row_count=0;

				do{
					row = mysql_fetch_row(result_set);
					if(!row)
						break;
					else if(row_count==0)
						{
							printf("\n%s  +------------------------------+\n",space);
                            printf("%s  |    AVAILABLE SKILL LEVEL     |--->",space);
						}
					printf(" %s,",row[0]);
					row_count++;

				}while(1);

				mysql_free_result(result_set);

				sprintf(query, "select distinct exposure_control from Camera");
				if (mysql_query(conn, query))
				{
					fprintf(stderr, "%s\n", mysql_error(conn));
					mysql_close(conn);
					exit(1);
				}
				result_set=mysql_use_result(conn);


				row_count=0;

				do
				{
					row = mysql_fetch_row(result_set);
					if(!row)
						break;
					else if(row_count==0)
					{
						    printf("\n%s  +------------------------------+\n",space);
                            printf("%s  |        AVAILABLE BRANDS      |--->",space);
					}
					printf(" %s,",row[0]);
					row_count++;
				}while(1);
                if(row_count)
                    printf("\n%s  +------------------------------+\n",space);
				mysql_free_result(result_set);


			}


			printf("\n\n");


			char temp_query[200];
			sprintf(query, "select * from Camera where (1 = 1)");
			printf("\n\n");
			printf("             Enter the brand (Enter None if not required): ");
            userInput(b);
            if(b[0] != '\0')
            {
                sprintf(temp_query," and brand_name = '%s'",b);
                strcat(query,temp_query);
            }
            printf("\n\n");

			printf("             Enter the Form Factor (Enter None if not required): ");
			userInput(c);
            if(c[0] != '\0')
            {
                sprintf(temp_query," and form_factor = '%s'",c);
                strcat(query,temp_query);
            }
			printf("\n\n");

			printf("             Enter the Skill Level (Enter None if not required): ");
			userInput(o);
            if(o[0] != '\0')
            {
                sprintf(temp_query," and skill_level = '%s'",o);
                strcat(query,temp_query);
            }
			printf("\n\n");

			printf("             Enter the Exposure Control (Enter None if not required): ");
			userInput(p);
            if(p[0] != '\0')
            {
                sprintf(temp_query," and exposure_control = '%s'",p);
                strcat(query,temp_query);
            }
			printf("\n\n");


			y:

			printf("%sPlease Enter A/a for Ascending order by price or D/d for Descending: ",space);
			char z;
			scanf(" %c",&z);
			getchar();

			if(z=='D'||z=='d')
			{
				sprintf(temp_query, " order by price desc");
                strcat(query,temp_query);
			}
            else if(z == 'A' || z== 'a')
			{
				sprintf(temp_query, " order by price");
                strcat(query,temp_query);
			}
			else
			{
				printf("Please enter a correct option\n");
				goto y;
			}
            printf("QUERY -> %s\n",query);
            if (mysql_query(conn, query))
            {
                fprintf(stderr, "%s\n", mysql_error(conn));
                mysql_close(conn);
                exit(1);
            }
			result_set = mysql_use_result(conn);

			system("clear");
			row_count=0;


			do
			{
				row = mysql_fetch_row(result_set);
				if(!row)
					break;
				else if(row_count==0)
				{
					printf("\n\n\n\n");
            		printf("%s+-------------------------------------------------------------------------------------------------------------------+\n",space);
            		printf("%s|                                                 PRODUCT - CAMERA                                                  |\n",space);
            		printf("%s+--------+------------+-------------+-------------+-----------------+------------+--------------+---------+---------+\n",space);
            		printf("%s|  S.No  | BRAND NAME | BRAND MODEL | FORM FACTOR |    SKILL LEVEL  | LENS TYPE  |   EXPOSURE   |  PRICE  |  COUNT  |\n",space);
            		printf("%s+--------+------------+-------------+-------------+-----------------+------------+--------------+---------+---------+\n",space);

				}
				//if(((strcmp(row[0],b)==0 ||strcmp(row[2],c)==0 || strcmp(row[3],o)==0 || strcmp(row[5],p)==0)) ||((!strlen(b))&&(!strlen(c))&&(!strlen(o))&&(!strlen(p))))
				//{
					printf("%s| %-6s | %-10s | %-11s | %-11s | %-15s | %-10s | %-12s | %-7s | %-7s |\n",space,row[8],row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7]);

				//}
				//printf("+------+------------+----------------+---------------------+------------------+------------+------------+--------------------+---------------------+-------+\n");
				row_count++;
			}while(1);
			if(row_count)
				printf("%s+--------+------------+-------------+-------------+-----------------+------------+--------------+---------+---------+\n",space);
			else
			{
			printf("\n\n\n\n                                      +---------------------------------------+\n");
        	printf("                                      | Sorry, This product does'nt exist.   |\n");
        	printf("                                      +---------------------------------------+\n");
			}

}

void phone(MYSQL *conn)
{
			system("clear");
			printf("\n\n\n\n");

			printf("                                                   Searching for Phone\n");
                        printf("\n\n");
			MYSQL_RES *result_set;
			MYSQL_ROW row;
			MYSQL_ROW row1;
			int row_count = 0;
			char space[17] = "             ";
			char query[600] = "";


			char b[50]="";
			char c[50]="";
            char o[50]="";
            char p[50]="";


			int a=1;
			if(a==1)
			{
				sprintf(query, "select distinct brand_name from Phone");
				if (mysql_query(conn, query))
				{
					fprintf(stderr, "%s\n", mysql_error(conn));
					mysql_close(conn);
					exit(1);
				}
				result_set=mysql_use_result(conn);
				do{
					row = mysql_fetch_row(result_set);
					if(!row)
						break;
					else if(row_count==0)
						{
							printf("\n%s  +------------------------------+\n",space);
                            printf("%s  |        AVAILABLE BRANDS      |--->",space);
						}
					printf(" %s,",row[0]);
					row_count++;
				}while(1);
				mysql_free_result(result_set);

				sprintf(query, "select distinct operating_system from Phone");
				if (mysql_query(conn, query))
				{
					fprintf(stderr, "%s\n", mysql_error(conn));
					mysql_close(conn);
					exit(1);
				}
				result_set=mysql_use_result(conn);


				row_count=0;

				do{
					row1 = mysql_fetch_row(result_set);
					if(!row1)
						break;
					else if(row_count==0)
						{
						    printf("\n%s  +------------------------------+\n",space);
                            printf("%s  |  AVAILABLE OPERATING SYSTEMS |--->",space);
						}
					printf(" %s,",row1[0]);
					row_count++;
				}while(1);

				mysql_free_result(result_set);

				sprintf(query, "select distinct processor from Phone");
				if (mysql_query(conn, query))
				{
					fprintf(stderr, "%s\n", mysql_error(conn));
					mysql_close(conn);
					exit(1);
				}
				result_set=mysql_use_result(conn);


				row_count=0;

				do{
					row1 = mysql_fetch_row(result_set);
					if(!row1)
						break;
					else if(row_count==0)
						{
							printf("\n%s  +------------------------------+\n",space);
                            printf("%s  |    AVAILABLE PROCESSORS      |--->",space);
						}
					printf(" %s,",row1[0]);
					row_count++;

				}while(1);


				mysql_free_result(result_set);

				sprintf(query, "select distinct wireless_carrier from Phone");
				if (mysql_query(conn, query))
				{
					fprintf(stderr, "%s\n", mysql_error(conn));
					mysql_close(conn);
					exit(1);
				}
				result_set=mysql_use_result(conn);


				row_count=0;

				do
				{
					row1 = mysql_fetch_row(result_set);
					if(!row1)
						break;
					else if(row_count==0)
					{
					        printf("\n%s  +------------------------------+\n",space);
                            printf("%s  | AVAILABLE WIRELESS CARRIERS  |--->",space);
					}
					printf(" %s,",row1[0]);
					row_count++;
				}while(1);

				if(row_count)
				    printf("\n%s  +------------------------------+\n",space);

				mysql_free_result(result_set);


			}

			printf("\n\n");

			char temp_query[200];
			sprintf(query, "select * from Phone where (1 = 1)");
			printf("\n\n");
			printf("             Enter the brand (Enter None if not required): ");
            userInput(b);
            if(b[0] != '\0')
            {
                sprintf(temp_query," and brand_name = '%s'",b);
                strcat(query,temp_query);
            }
            printf("\n\n");

			printf("             Enter the Operating System (Enter None if not required): ");
			userInput(c);
            if(c[0] != '\0')
            {
                sprintf(temp_query," and operating_system = '%s'",c);
                strcat(query,temp_query);
            }
			printf("\n\n");

			printf("             Enter the Processor (Enter None if not required): ");
			userInput(o);
            if(o[0] != '\0')
            {
                sprintf(temp_query," and processor = '%s'",o);
                strcat(query,temp_query);
            }
			printf("\n\n");

			printf("             Enter the Wireless Carrier (Enter None if not required): ");
			userInput(p);
            if(p[0] != '\0')
            {
                sprintf(temp_query," and wireless_carrier = '%s'",p);
                strcat(query,temp_query);
            }
			printf("\n\n");


			y:

			printf("%sPlease Enter A/a for Ascending order by price or D/d for Descending: ",space);
			char z;
			scanf(" %c",&z);
			getchar();

			if(z=='D'||z=='d')
			{
				sprintf(temp_query, " order by price desc");
                strcat(query,temp_query);
			}
            else if(z == 'A' || z== 'a')
			{
				sprintf(temp_query, " order by price");
                strcat(query,temp_query);
			}
			else
			{
				printf("Please enter a correct option\n");
				goto y;
			}
            printf("QUERY -> %s\n",query);
            if (mysql_query(conn, query))
            {
                fprintf(stderr, "%s\n", mysql_error(conn));
                mysql_close(conn);
                exit(1);
            }
			result_set = mysql_use_result(conn);


			system("clear");
			row_count=0;


		do
			{
				row = mysql_fetch_row(result_set);
				if(!row)
					break;
				else if(row_count==0)
				{
					printf("\n\n\n\n");
            		printf("+--------+------------+-------------+-----------------+------------------+------------+------------+------------+-------------+--------------+---------+\n");
            		printf("|                                                               PRODUCT PHONE                                                                          |\n");
            		printf("+--------+------------+-------------+-----------------+------------------+------------+------------+------------+-------------+--------------+---------+\n");
            		printf("|  S.No  | BRAND NAME | BRAND MODEL |    PROCESSOR    | OPERATING SYSTEM |  CELLULAR  |   COLOUR   |  CARRIER   | SCREEN SIZE |    PRICE     |  COUNT  |\n");
            		printf("+--------+------------+-------------+-----------------+------------------+------------+------------+------------+-------------+--------------+---------+\n");
				}

					printf("| %-6s | %-10s | %-11s | %-15s |    %-10s    | %-10s | %-10s | %-10s |   %-7s   | %-12s | %-7s |\n",row[10],row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9]);

				row_count++;
			}while(1);
			if(row_count)
				printf("+--------+------------+-------------+-----------------+------------------+------------+------------+------------+-------------+--------------+---------+\n");
			else
				{
				printf("\n\n\n\n                                      +---------------------------------------+\n");
        		printf("                                      | Sorry, This product does'nt exist.  |\n");
        		printf("                                      +---------------------------------------+\n");
			}
}



void refrigerator(MYSQL *conn)
{
	system("clear");
			printf("\n\n\n\n");

			printf("                                            Searching for Refrigerator\n");
            printf("\n\n");
			MYSQL_RES *result_set;
			MYSQL_ROW row;
			MYSQL_ROW row1;
			int row_count = 0;
			char space[17] = "             ";
			char query[600] = "";


			char b[50]="";
			char c[50]="";
            //char o[50]="";
            //char p[50]="";


			int a=1;
			if(a==1)
			{
				sprintf(query, "select distinct brand_name from Refrigerator");
				if (mysql_query(conn, query))
				{
					fprintf(stderr, "%s\n", mysql_error(conn));
					mysql_close(conn);
					exit(1);
				}
				result_set=mysql_use_result(conn);
				do{
					row = mysql_fetch_row(result_set);
					if(!row)
						break;
					else if(row_count==0)
						{
							printf("\n%s  +------------------------------+\n",space);
                            printf("%s  |        AVAILABLE BRANDS      |--->",space);
						}
					printf(" %s,",row[0]);
					row_count++;
				}while(1);

				mysql_free_result(result_set);

				sprintf(query, "select distinct capacity from Refrigerator");
				if (mysql_query(conn, query))
				{
					fprintf(stderr, "%s\n", mysql_error(conn));
					mysql_close(conn);
					exit(1);
				}
				result_set=mysql_use_result(conn);


				row_count=0;

				do{
					row1 = mysql_fetch_row(result_set);
					if(!row1)
						break;
					else if(row_count==0)
						{
							printf("\n%s  +------------------------------+\n",space);
                            printf("%s  |     AVAILABLE CAPACITIES     |--->",space);
						}
					printf(" %s,",row1[0]);
					row_count++;
				}while(1);


/*
				sprintf(query, "select distinct color from Refrigerator");
				if (mysql_query(conn, query))
				{
					fprintf(stderr, "%s\n", mysql_error(conn));
					mysql_close(conn);
					exit(1);
				}
				result_set=mysql_use_result(conn);


				row_count=0;

				do{
					row1 = mysql_fetch_row(result_set);
					if(!row1)
						break;
					else if(row_count==0)
						{
							printf("\n%s  +------------------------------+\n",space);
                            printf("%s  |      AVAILABLE COLOURS       |--->",space);
						}
					printf(" %s,",row1[0]);
					row_count++;

				}while(1);

				mysql_free_result(result_set);

				sprintf(query, "select distinct no_of_doors from Refrigerator");
				if (mysql_query(conn, query))
				{
					fprintf(stderr, "%s\n", mysql_error(conn));
					mysql_close(conn);
					exit(1);
				}
				result_set=mysql_use_result(conn);


				row_count=0;

				do
				{
					row1 = mysql_fetch_row(result_set);
					if(!row1)
						break;
					else if(row_count==0)
					{
						    printf("\n%s  +------------------------------+\n",space);
                            printf("%s  |    AVAILABLE DOOR COUNT      |--->",space);
					}
					printf(" %s,",row1[0]);
					row_count++;
				}while(1);
*/
				if(row_count)
                    printf("\n%s  +------------------------------+\n",space);

				mysql_free_result(result_set);


}


			char temp_query[200];
			sprintf(query, "select * from Refrigerator where (1 = 1)");
			printf("\n\n");
			printf("             Enter the brand (Enter None if not required): ");
            userInput(b);
            if(b[0] != '\0')
            {
                sprintf(temp_query," and brand_name = '%s'",b);
                strcat(query,temp_query);
            }
            printf("\n\n");

			printf("             Enter the Total Capacity (Enter None if not required): ");
			userInput(c);
            if(c[0] != '\0')
            {
                sprintf(temp_query," and capacity = '%s'",c);
                strcat(query,temp_query);
            }
			printf("\n\n");


			y:

			printf("%sPlease Enter A/a for Ascending order by price or D/d for Descending: ",space);
			char z;
			scanf(" %c",&z);
			getchar();

			if(z=='D'||z=='d')
			{
				sprintf(temp_query, " order by price desc");
                strcat(query,temp_query);
			}
            else if(z == 'A' || z== 'a')
			{
				sprintf(temp_query, " order by price");
                strcat(query,temp_query);
			}
			else
			{
				printf("Please enter a correct option\n");
				goto y;
			}
            printf("QUERY -> %s\n",query);
            if (mysql_query(conn, query))
            {
                fprintf(stderr, "%s\n", mysql_error(conn));
                mysql_close(conn);
                exit(1);
            }
			result_set = mysql_use_result(conn);


			system("clear");
			row_count=0;

			do
			{
				row = mysql_fetch_row(result_set);
				if(!row)
					break;
				else if(row_count==0)
				{
					printf("\n\n\n\n");
            		printf("%s+-------------------------------------------------------------------------------+\n",space);
            		printf("%s|                            PRODUCT REFRIGERATOR                               |\n",space);
            		printf("%s+--------+------------+-------------+----------+-------+------------+-----------+\n",space);
            		printf("%s|  S.No  | BRAND NAME | BRAND MODEL | CAPACITY | DOORS |   PRICE    |   COUNT   |\n",space);
            		printf("%s+--------+------------+-------------+----------+-------+------------+-----------+\n",space);

				}
				printf("%s| %-6s | %-10s | %-11s | %-8s | %-5s | %-10s | %-9s |\n",space,row[6],row[0],row[1],row[2],row[3],row[4],row[5]);



				row_count++;
			}while(1);
			if(row_count)
				printf("%s+--------+------------+-------------+----------+-------+------------+-----------+\n",space);
			else{
			printf("\n\n\n\n                                      +---------------------------------------+\n");
        	printf("                                      | Sorry, This product does'nt exist.    |\n");
        	printf("                                      +---------------------------------------+\n");
			}

}

void search_sub_menu(void)
{
	printf("\e[1;1H\e[2J");
	int  user_input;
	char *host ="helios.vse.gmu.edu";
	char *user ="jsamson6";//"jsamson6";
	char *pass = "";
	char *dbname = "jsamson6";
    int  index=0;
    char buff[50]="";
    char query[600]="";
    char space[15]="             ";
	MYSQL_ROW row;
	int ind=0;
	MYSQL_RES *result_set;
	//MYSQL_ROW row;
	MYSQL_ROW row1;

	MYSQL *conn;
	conn = mysql_init(NULL);
	if (!(mysql_real_connect(conn,host, user, pass,dbname,0,NULL,0)))
	{
		fprintf(stderr, "\nError %s [%d]\n", mysql_error(conn), mysql_errno(conn));
		exit(1);
	}
	top:
	index=0;
    printf("\n\n\n\n");
	//int n;

	printf("\e[1;1H\e[2J");
	if(ind==1)
	{
		printf("\n\n%sError: entered product doesn't exist in the product table\n\n",space);
        ind = 0;

	}
	display_product_list(conn);

    printf("\n\n%sPlease select a product from the above displayed list: ",space);

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
		printf("%s",query);
        if (mysql_query(conn, query))
        {
            fprintf(stderr, "%s\n", mysql_error(conn));
            mysql_close(conn);
            exit(1);
        }

        result_set = mysql_store_result(conn);

        //row = mysql_fetch_row(result_set);
		//printf("ind= %d %d",ind,mysql_num_rows(result_set));
        if(!mysql_num_rows(result_set))
        {
            ind = 1;
			memset(buff,'\0',sizeof(buff));
			goto top;

        }


			printf("                          Searching for Product\n");
            printf("\n\n");
			//MYSQL_RES *result_set;
			//MYSQL_ROW row;
			//MYSQL_ROW row1;
			int row_count = 0;
   //printf("buff = %s\n",buff);
    if(!strcmp(buff,"Laptop"))
    {
        laptop(conn);
    }
    else if(!strcmp(buff,"Refrigerator"))
        refrigerator(conn);
    else if(!strcmp(buff,"Phone"))
        phone(conn);
    else if(!strcmp(buff,"Camera"))
        Camera(conn);
    else
    {
            printf("                                                   Searching for %s\n",buff);
			char b[50]="";
			char c[50]="";

            printf("\e[1;1H\e[2J");
            printf("\n\n\n\n");
			int a=1;
			if(a==1)
			{
				sprintf(query, "select distinct brand_name from %s",buff);
				if (mysql_query(conn, query))
				{
					fprintf(stderr, "%s\n", mysql_error(conn));
					mysql_close(conn);
					exit(1);
				}
				result_set=mysql_use_result(conn);
				do{
					row = mysql_fetch_row(result_set);
					if(!row)
						break;
					else if(row_count==0)
						{
							printf("\n%s  +------------------------------+\n",space);
                            printf("%s  |        AVAILABLE BRANDS      |--->",space);
						}
					printf(" %s,",row[0]);
					row_count++;
				}while(1);

				mysql_free_result(result_set);
			}
			sprintf(query, "select distinct brand_model from %s",buff);
			if (mysql_query(conn, query))
			{
				fprintf(stderr, "%s\n", mysql_error(conn));
				mysql_close(conn);
				exit(1);
			}
			result_set=mysql_use_result(conn);
			row_count=0;
			do{
				row1 = mysql_fetch_row(result_set);
				if(!row1)
					break;
				else if(row_count==0)
				{
				    printf("\n%s  +------------------------------+\n",space);
                    printf("%s  |        AVAILABLE MODELS      |--->",space);
				}
					printf(" %s,",row1[0]);
					row_count++;
			}while(1);
			if(row_count)
			    printf("\n%s  +------------------------------+\n",space);
			mysql_free_result(result_set);


			printf("\n\n");


			char temp_query[200];
			sprintf(query, "select * from %s where (1 = 1)",buff);
			printf("\n\n");
			printf("             Enter the brand (Enter None if not required): ");
            userInput(b);
            if(b[0] != '\0')
            {
                sprintf(temp_query," and brand_name = '%s'",b);
                strcat(query,temp_query);
            }
            printf("\n\n");

			printf("             Enter the brand model (Enter None if not required): ");
			userInput(c);
            if(c[0] != '\0')
            {
                sprintf(temp_query," and brand_model = '%s'",c);
                strcat(query,temp_query);
            }
			printf("\n\n");


			y:

			printf("%sPlease Enter A/a for Ascending order by price or D/d for Descending: ",space);
			char z;
			scanf(" %c",&z);
			getchar();

			if(z=='D'||z=='d')
			{
				sprintf(temp_query, " order by price desc");
                strcat(query,temp_query);
			}
            else if(z == 'A' || z== 'a')
			{
				sprintf(temp_query, " order by price");
                strcat(query,temp_query);
			}
			else
			{
				printf("Please enter a correct option\n");
				goto y;
			}
            printf("QUERY -> %s\n",query);
            if (mysql_query(conn, query))
            {
                fprintf(stderr, "%s\n", mysql_error(conn));
                mysql_close(conn);
                exit(1);
            }
			result_set = mysql_use_result(conn);


			system("clear");
			row_count=0;


			do
			{
				row = mysql_fetch_row(result_set);
				if(!row)
					break;
				else if(row_count==0)
				{
						printf("\n\n\n\n");
           				printf("%s+-------------------------------------------------------------------+\n",space);
            			printf("%s|                      PRODUCT %-30s       |\n",space,buff);
            			printf("%s+--------+------------+-------------+------------+------------------+\n",space);
            			printf("%s|  S.No  | BRAND NAME | BRAND MODEL |   PRICE    | AVAILABLE PIECES |\n",space);
            			printf("%s+--------+------------+-------------+------------+------------------+\n",space);
				}
				if(((strcmp(row[0],b)==0 || strcmp(row[1],c)==0) ||((!strlen(b))&&(!strlen(c)))))
				{
					printf("%s| %-6s | %-10s | %-11s | %-10s | %-16s |\n",space,row[4],row[0],row[1],row[2],row[3]);
				}
				//printf("+------+------------+----------------+-----------------+------------------+------------+------------+--------------------+---------------------+-------+\n");
				row_count++;
			}while(1);
			if(row_count)
				printf("%s+--------+------------+-------------+------------+------------------+\n",space);
			else
			{
			printf("\n\n\n\n                                      +---------------------------------------+\n");
        	printf("                                      | Sorry, This product does'nt exist.    |\n");
        	printf("                                      +---------------------------------------+\n");
			}
	}
	printf("\n\n\n\n             Enter any key to go back to the menu: ");
	while((user_input = getchar()) != EOF)
	{
		if(user_input == '\n')
		break;
	}

}


