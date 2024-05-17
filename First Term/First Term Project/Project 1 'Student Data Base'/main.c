/*
 * main.c
 *
 *  Created on: Apr 28, 2024
 *      Author: nemad
 */
#include "Student_Management_System.h"

int main()
{
	FIFO_init(&student_managment, buf , 55);
	int option;
	DPRINTF("\nWelcome to the Student Management System :)");
	while(1)
	{
		DPRINTF("\n------------------------------------");
		DPRINTF("\nChoose one of the task you want to perform:  ");
		DPRINTF("\n1:Add the Students details manually.");
		DPRINTF("\n2:Add the Student details from Text File. ");
		DPRINTF("\n3:Find the Student details by Roll number. ");
		DPRINTF("\n4:Find the Student details by First name.");
		DPRINTF("\n5:Find the Student details by course ID.");
		DPRINTF("\n6:Find the total number of students.");
		DPRINTF("\n7:Delete the Student details by Roll Number.");
		DPRINTF("\n8:Update the Student Details by Roll Number.");
		DPRINTF("\n9:View all Students.");
		DPRINTF("\n10:Exit");
		DPRINTF("\nEnter your choice to perform the task : ");
		scanf("%d",&option);
		switch(option)
		{
		case 1:
			FIFO_Add_Manually(&student_managment);
			break;
		case 2:
			FIFo_add_from_file(&student_managment);
			break;
		case 3:
			Find_by_roll(&student_managment);
			break;
		case 4:
			Find_by_fname(&student_managment);
			break;
		case 5:
			Find_by_cID(&student_managment);
			break;
		case 6:
			total_number(&student_managment);
			break;
		case 7:
			delete_student(&student_managment);
			break;
		case 8:
			update_student(&student_managment);
			break;
		case 9:
			view_student(&student_managment);
			break;
		case 10:
			DPRINTF("\nExiting the Student Managment System program.");
			exit(0);
		default:
			DPRINTF("\nWrong Choice!");
			break;

		}

	}
}

