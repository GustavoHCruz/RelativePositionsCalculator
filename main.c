#include "lib.h"

void main()
{
	FILE *arq;
	char x[10], y[10], namearq[30];
	float ret;
	int option, answer, confir = 0, changes, temp = 0, r;

	space e;

	system("cls");

	r = dynamic_menu("Welcome to the Relative Positions Calculator. Do you want to load any previously saved space?", 2, 2, "Yes", "No");
	do
	{
		if (r == 1)
		{
			do
			{
				printf("File name:");
				fflush(stdin);
				input(namearq, 30);
				strcat(namearq, ".cpr");
				setbuf(stdin, NULL);
				answer = login(&arq, namearq, &e);
				if (answer == 1)
				{
					printf("Successfully loaded\n");
					confir = 1;
					confir = 1;
				}
				else
				{
					printf("\nFile not find\n\n");
					confir = 0;
					system("pause");
					system("cls");
					r = dynamic_menu("Try again?", 2, 2, "Yes", "No");
					if (r == 2)
					{
						printf("Closing application.");
						exit(1);
					}
					else if (r == 1)
					{
						system("pause");
						system("cls");
					}
					else
					{
						printf("Command not recognised\n");
						system("pause");
						system("cls");
					}
				}
			} while (confir == 0);
		}
		else if (r == 2)
		{
			printf("\n");
			system("pause");
			system("cls");
			r = dynamic_menu("Create a new file?", 2, 2, "Yes", "No");
			if (r == 1)
			{
				printf("File name:");
				fflush(stdin);
				input(namearq, 30);
				printf("\n");
				strcat(namearq, ".cpr");
				setbuf(stdin, NULL);
				answer = create_space(namearq, &e, &arq);
				if (answer == 0)
				{
					printf("Internal error\n");
					system("pause");
					exit(1);
				}
				else
				{
					printf("Sucessfully created\n");
					save(arq, &e);
				}
				confir = 1;
			}
			else
			{
				system("pause");
				system("cls");
				r = dynamic_menu("Continue without saving?", 2, 2, "Yes", "No");
				if (r == 1)
				{
					temp = 1;
					confir = 1;
					create_space_temp(&e);
				}
				else
					exit(0);
			}
		}
		if (confir != 1)
		{
			printf("Invalid entry, please try again\nAnswer:");
			fflush(stdin);
			scanf("%i", &r);
			setbuf(stdin, NULL);
		}
	} while (confir != 1);

	//Menu
	short pointLimiter, vectorLimiter, lineLimiter, planeLimiter;

	do
	{
	begin:
		printf("\n");
		system("pause");
		system("cls");
		option = dynamic_menu("==================OPTIONS MENU==================", 8, 8, "Points operations", "Vectors operations", "Lines operations", "Planes operations", "Print space", "Delete all", "Save", "Exit");

		system("cls");

		switch (option)
		{
		case 1: //Points operations
			if (e.point_amount == 0)
				pointLimiter = 2;
			else if (e.point_amount == 1)
				pointLimiter = 5;
			else
				pointLimiter = 6;
			do
			{
				answer = dynamic_menu("==================POINTS==================", 6, pointLimiter, "Back", "Add Point", "Print all Points", "Delete Point", "Delete all Points", "Calculate distance between two Points");

				system("cls");

				if (answer == 1)
					goto begin;
				else if (answer == 2) //Push
				{
					char name_point[10];
					float P[3];

					printf("Point name:");
					fflush(stdin);
					input(name_point, 10);

					printf("\nPoint coordinate\n");
					printf("X:");
					fflush(stdin);
					scanf("%f", &P[0]);
					printf("Y:");
					fflush(stdin);
					scanf("%f", &P[1]);
					printf("Z:");
					fflush(stdin);
					scanf("%f", &P[2]);
					printf("\n");

					point_push(&e, name_point, P);

					changes = 1;
					goto begin;
				}
				else if (answer == 3) //Print
				{
					point_print(&e);
					goto begin;
				}
				else if (answer == 4) //Pop
				{
					printf("Point:");
					fflush(stdin);
					input(x, 10);
					printf("\n");
					answer = point_pop(&e, x);
					if (answer == 1)
					{
						printf("Point deleted\n");
						changes = 1;
					}
					else
						printf("Cannot find the point");
					goto begin;
				}
				else if (answer == 5) //Destroy
				{
					r = dynamic_menu("Continue? This action has no going back", 2, 2, "Yes", "No");
					if (r == 1)
					{
						point_destroy(&e);

						printf("All Points has successful erased\n");
						changes = 1;
					}
					else
						printf("Operation canceled\n");
					goto begin;
				}
				else if (answer == 6) //Calculate distance
				{
					printf("First Point:");
					fflush(stdin);
					input(x, 10);
					printf("Second Points:");
					fflush(stdin);
					input(y, 10);
					printf("\n");
					ret = point_distance(&e, x, y);
					if (ret == 0)
					{
						printf("Error\n");
					}
					else
					{
						printf("Distance between the Points: %.2f\n", ret);
					}
					goto begin;
				}
			} while (1);
		case 2: //Vectors operations

			if (e.vector_amount == 0)
				vectorLimiter = 2;
			else if (e.vector_amount == 1)
				vectorLimiter = 5;
			else
				vectorLimiter = 6;
			do
			{
				answer = dynamic_menu("==================VECTORS==================", 6, vectorLimiter, "Back", "Add Vector", "Print all Vectors", "Delete Vector", "Delete all Vectors", "Calculate linearity between Vectors");

				system("cls");

				if (answer == 1)
					goto begin;
				else if (answer == 2) //Push
				{
					char name_vector[10];
					float V[3];
					r = 0;

					printf("Vector:");
					fflush(stdin);
					input(name_vector, 10);

					system("cls");

					if (e.point_amount > 1)
					{
						r = dynamic_menu("Create the Vector from two Points?", 2, 2, "Yes", "No");
					}
					if (r == 1)
					{
						char a[10], b[10];
						printf("First Point:");
						fflush(stdin);
						input(a, 10);
						printf("Second Points:");
						fflush(stdin);
						input(b, 10);
						r = vector_pushAlt(&e, a, b, name_vector);
						if (r == 0)
							printf("Not able to find the Points, aborting operation\n");
						else
							changes = 1;
					}
					else
					{
						printf("Vector coordinates\n");
						printf("X:");
						fflush(stdin);
						scanf("%f", &V[0]);
						printf("Y:");
						fflush(stdin);
						scanf("%f", &V[1]);
						printf("Z:");
						fflush(stdin);
						scanf("%f", &V[2]);
						printf("\n");

						vector_push(&e, name_vector, V);

						changes = 1;
					}
					goto begin;
				}
				else if (answer == 3) //Print
				{
					vector_print(&e);
					goto begin;
				}
				else if (answer == 4) //Pop
				{
					printf("Vector:");
					fflush(stdin);
					input(x, 10);
					printf("\n");
					answer = vector_pop(&e, x);
					if (answer == 1)
					{
						printf("Vector deleted\n");
						changes = 1;
					}
					else
						printf("Not able to find the Vector\n");
					goto begin;
				}
				else if (answer == 5) //Destroy
				{
					r = dynamic_menu("Continue? This action has no going back", 2, 2, "Yes", "No");
					if (r == 1)
					{
						vector_destroy(&e);
						printf("All Vectors has successful erased\n");
						changes = 1;
					}
					else
						printf("Operation canceled\n");
					goto begin;
				}
				else if (answer == 6) //Calculate relative position
				{
					char vec1[10], vec2[10], vec3[10];
					int amount;
					printf("Number of vectors to be analysed:");
					fflush(stdin);
					scanf("%i", amount);

					if (amount == 1)
					{
						r = 1;
					}
					else if (amount == 2)
					{
						printf("First Vector:");
						fflush(stdin);
						input(vec1, 10);
						printf("Second Vector:");
						fflush(stdin);
						input(vec2, 10);
						printf("\n");
						r = vector_linearity(&e, amount, vec1, vec2, "");
					}
					else if (amount == 3)
					{
						printf("First Vector:");
						fflush(stdin);
						input(vec1, 10);
						printf("Second Vector:");
						fflush(stdin);
						input(vec2, 10);
						printf("Third Vector:");
						fflush(stdin);
						input(vec3, 10);
						printf("\n");
						r = vector_linearity(&e, amount, vec1, vec2, vec3);
					}
					else
						r = 1;

					if (r == 0)
					{
						printf("Error\n");
					}
					else if (r == 1)
					{
						printf("Linearly Dependent\n");
					}
					else
						printf("Linearly Independent\n");
					goto begin;
				}
			} while (1);
		case 3: //Lines operations
			if (e.line_amount == 0)
				lineLimiter = 2;
			else if (e.line_amount == 1)
				lineLimiter = 5;
			else
				lineLimiter = 7;
			do
			{
				answer = dynamic_menu("==================LINES==================", 7, lineLimiter, "Back", "Add Line", "Print all Lines", "Delete Line", "Delete all Lines", "Calculate distance between two Lines", "Calculate relative position between two Lines");

				system("cls");

				if (answer == 1)
					goto begin;
				else if (answer == 2) //Push
				{
					char name_line[10];
					float P[3], V[3];
					r = 0;

					printf("Line:");
					fflush(stdin);
					input(name_line, 10);

					printf("\nPoint coordinates\n");
					printf("X:");
					fflush(stdin);
					scanf("%f", &P[0]);
					printf("Y:");
					fflush(stdin);
					scanf("%f", &P[1]);
					printf("Z:");
					fflush(stdin);
					scanf("%f", &P[2]);
					printf("\n");

					printf("\nVector coordinates\n");
					printf("X:");
					fflush(stdin);
					scanf("%f", &V[0]);
					printf("Y:");
					fflush(stdin);
					scanf("%f", &V[1]);
					printf("Z:");
					fflush(stdin);
					scanf("%f", &V[2]);
					printf("\n");

					line_push(&e, name_line, P, V);

					changes = 1;
					goto begin;
				}
				else if (answer == 3) //Print
				{
					line_print(&e);
					;
					goto begin;
				}
				else if (answer == 4) //Pop
				{
					printf("Line:");
					fflush(stdin);
					input(x, 10);
					printf("\n");
					answer = line_pop(&e, x);
					if (answer == 1)
					{
						printf("Line deleted\n");
						changes = 1;
					}
					else
						printf("Not able to find the Line\n");
					goto begin;
				}
				else if (answer == 5) //Destroy
				{
					r = dynamic_menu("Continue? This action has no going back", 2, 2, "Yes", "No");
					if (r == 1)
					{
						line_destroy(&e);
						printf("All Lines has successful erased\n");
						changes = 1;
					}
					else
						printf("Operation canceled\n");
					goto begin;
				}
				else if (answer == 6) //Calculate distance
				{
					printf("First Line:");
					fflush(stdin);
					input(x, 10);
					printf("\nSecond Line:");
					fflush(stdin);
					input(y, 10);

					ret = line_distance(&e, x, y);

					printf("\nDistance between the Lines: %.2f\n", ret);
					goto begin;
				}
				else if (answer == 7) //Calculate relative position
				{
					printf("First Line:");
					fflush(stdin);
					input(x, 10);
					printf("\nSecond Line:");
					fflush(stdin);
					input(y, 10);

					r = line_relativity(&e, x, y);

					if (r == 1)
					{
						printf("\nReverse Lines\n");
					}
					else if (r == 2)
					{
						printf("\nParallel Lines\n");
					}
					else if (r == 3)
					{
						printf("\nConcurrent Lines\n");
					}
					else if (r == 4)
					{
						printf("\nCoincident lines\n");
					}
					else
						printf("\nError\n");
					goto begin;
				}
			} while (1);
		case 4: //Planes operations
			if (e.plane_amount == 0)
				planeLimiter = 2;
			else if (e.plane_amount == 1)
				planeLimiter = 5;
			else
				planeLimiter = 7;
			do
			{
				answer = dynamic_menu("==================PLANES==================", 7, planeLimiter, "Back", "Add Plane", "Print all Planes", "Delete Plane", "Delete all Planes", "Calculate distance between two Planes", "Calculate relative position between two Planes");

				system("cls");

				if (answer == 1)
					goto begin;
				else if (answer == 2) //Push
				{
					char name_plane[10];
					float P[3], V1[3], V2[3];
					r = 0;

					printf("Plane:");
					fflush(stdin);
					input(name_plane, 10);

					printf("\nPoint coordinates\n");
					printf("X:");
					fflush(stdin);
					scanf("%f", &P[0]);
					printf("Y:");
					fflush(stdin);
					scanf("%f", &P[1]);
					printf("Z:");
					fflush(stdin);
					scanf("%f", &P[2]);
					printf("\n");

					printf("\nFirst Vector coordinates\n");
					printf("X:");
					fflush(stdin);
					scanf("%f", &V1[0]);
					printf("Y:");
					fflush(stdin);
					scanf("%f", &V1[1]);
					printf("Z:");
					fflush(stdin);
					scanf("%f", &V1[2]);
					printf("\n");

					printf("\nSecond Vector coordinates\n");
					printf("X:");
					fflush(stdin);
					scanf("%f", &V2[0]);
					printf("Y:");
					fflush(stdin);
					scanf("%f", &V2[1]);
					printf("Z:");
					fflush(stdin);
					scanf("%f", &V2[2]);
					printf("\n");

					if (vector_linearity_2vec(V1, V2) == 1)
						printf("To obtain a plane, two Linear Independence Vectors are required, operation aborted\n");
					else
					{
						plane_push(&e, name_plane, P, V1, V2);
						changes = 1;
					}
					goto begin;
				}
				else if (answer == 3) //Print
				{
					plane_print(&e);
					goto begin;
				}
				else if (answer == 4) //Pop
				{
					printf("Plane:");
					fflush(stdin);
					input(x, 10);
					printf("\n");
					answer = plane_pop(&e, x);
					if (answer == 1)
					{
						printf("Plane deleted\n");
						changes = 1;
					}
					else
						printf("Not able to find the Plane\n");
					goto begin;
				}
				else if (answer == 5) //Destroy
				{
					r = dynamic_menu("Continue? This action has no going back", 2, 2, "Yes", "No");
					if (r == 1)
					{
						plane_destroy(&e);
						printf("All Planes has successful erased\n");
						changes = 1;
					}
					else
						printf("Operation canceled\n");
					goto begin;
				}
				else if (answer == 6) //Calculate distance
				{
					printf("First Plane:");
					fflush(stdin);
					input(x, 10);
					printf("\nSecond Plane:");
					fflush(stdin);
					input(y, 10);

					ret = plane_distance(&e, x, y);

					printf("\nThe distance between the Planes is: %.2f\n", ret);
					goto begin;
				}
				else if (answer == 7) //Calculate relative position
				{
					printf("First Plane:");
					fflush(stdin);
					input(x, 10);
					printf("\nSecond Plane:");
					fflush(stdin);
					input(y, 10);

					r = plane_relativity(&e, x, y);

					if (r == 1)
						printf("\nParallel Planes\n");
					else if (r == 2)
						printf("\nConcurrent Planes\n");
					else
						printf("\nError\n");
					goto begin;
				}
			} while (1);
		case 5: //Print Space
			print_space(&e);
			break;
		case 6: //Delete space
			r = dynamic_menu("Continue? This action has no going back", 2, 2, "Yes", "No");
			if (r == 1)
			{
				destroy_space(&e);
				printf("All data has successful erase\n");
				changes = 1;
			}
			else
				printf("Operation canceled\n");
			break;
		case 7: //Save
			if (temp == 1)
				printf("You cannot save a temporary file\n");
			else
			{
				answer = save(arq, &e);
				if (answer == 1)
				{
					printf("Saved\n");
					changes = 0;
				}
				else
					printf("Internal error\n");
			}
			break;
		case 8: //Exit
			printf("Closing application\n\n");

			if (temp == 0)
			{
				if (changes == 1)
				{
					r = dynamic_menu("There are unsaved changes, do you want to save?", 2, 2, "Yes", "No");
					if (r == 1)
					{
						answer = save(arq, &e);
						if (answer == 1)
							printf("Saved\n\n");
						else
							printf("Internal error\n\n");
					}
				}
				logout(arq, &e);
			}
			exit(0);
			break;
		}

	} while (1);
}