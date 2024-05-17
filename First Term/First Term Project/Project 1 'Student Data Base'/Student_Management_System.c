/*
 * Student_Management_System.c
 *
 *  Created on: Apr 28, 2024
 *      Author: nemad
 */
#include "Student_Management_System.h"

FIFO_Buf_status FIFO_init(FIFO_Buf * fifo, sInfo* buf , unsigned int length)
{
	if(buf == NULL)
	{
		return FIFO_Null;
	}
	fifo->base = buf;
	fifo->head = buf;
	fifo->tail = buf;
	fifo->length = length;
	fifo->count = 0;
	return FIFO_no_error;
}
int check_roll_number(FIFO_Buf* fifo, int roll)
{
	sInfo* pCheck = fifo->base;
	for(int i =0; i<fifo->count;i++)
	{
		if(pCheck->roll == roll)
		{
			return 1;
		}
		pCheck++;
	}
	return 0;
}
FIFO_Buf_status FIFO_Add_Manually(FIFO_Buf* fifo)
{
	char temp_str[30];
	int temp_int;
	if(!fifo->base || !fifo->head || !fifo->tail)
	{
		return FIFO_Null;
	}
	if(fifo->count == fifo->length)
	{
		return FIFO_Full;
	}


	DPRINTF("\n--------------------------------");
	DPRINTF("\nAdd the Student Details : ");
	DPRINTF("\n--------------------------------");
	DPRINTF("\nEnter the Roll Number: ");
	gets(temp_str);
	temp_int = atoi(temp_str);
	if(check_roll_number(fifo,temp_int)==1)
	{
		DPRINTF("\n[ERROR] Roll Number is taken before.");
		return FIFO_error;
	}
	fifo->head->roll = temp_int;
	DPRINTF("\nEnter the first name of student: ");
	gets(fifo->head->fname);
	DPRINTF("\nEnter the last name of student: ");
	gets(fifo->head->lname);
	DPRINTF("\nEnter the GPA you obtained: ");
	gets(temp_str);
	fifo->head->GPA= atof(temp_str);
	DPRINTF("\nEnter the course ID of each course: ");
	for(int i =0 ; i< 5;i++)
	{
		DPRINTF("\nCourse %d ID is: ", i+1);
		gets(temp_str);
		fifo->head->cid[i] = atoi(temp_str);
	}
	fifo->head ++;
	fifo->count ++;
	DPRINTF("\n[INFO] Student Details is added successfully !");
	DPRINTF("\nThe total number of Students is %d.", fifo->count);
	DPRINTF("\nYou can add %d more Students.", 50-(fifo->count));
	return FIFO_no_error;
}
FIFO_Buf_status Find_by_roll(FIFO_Buf* fifo)
{
	sInfo* currentStudent = fifo->base;
	char temp_str[30];
	int temp_int;
	if(!fifo->base || !fifo->head || !fifo->tail)
	{
		return FIFO_Null;
	}
	if(fifo->count == 0)
	{
		DPRINTF("No Registered Students yet.");
		return FIFO_empty;
	}
	DPRINTF("\nEnter the Roll Number of the student: ");
	gets(temp_str);
	temp_int = atoi(temp_str);

	for(int i = 0; i<fifo->count;i++)
	{
		if(temp_int == currentStudent->roll)
		{
			DPRINTF("\nThe Student Details are : ");
			DPRINTF("\nThe first name is %s", currentStudent->fname);
			DPRINTF("\nThe last name is %s", currentStudent->lname);
			DPRINTF("\nThe GPA is %.2f",currentStudent->GPA);
			for(int y = 0; y<5;y++)
			{
				DPRINTF("\nCourse %d ID is %d",y+1,currentStudent->cid[y]);
			}
			return FIFO_no_error;
		}
		currentStudent++;

	}
	DPRINTF("\n[ERROR] Roll Number not found !");
	return FIFO_error;

}
FIFO_Buf_status Find_by_fname(FIFO_Buf* fifo)
{
	sInfo* currentStudent = fifo->base;
	char temp_str[30];
	if(!fifo->base || !fifo->head || !fifo->tail)
	{
		return FIFO_Null;
	}
	if(fifo->count == 0)
	{
		DPRINTF("No Registered Students yet.");
		return FIFO_empty;
	}
	DPRINTF("\nEnter the First name of the student: ");
	gets(temp_str);

	for(int i = 0; i<fifo->count;i++)
	{
		if(strcmpi(currentStudent->fname, temp_str)== 0)
		{
			DPRINTF("\nThe Student Details are : ");
			DPRINTF("\nThe first name is %s", currentStudent->fname);
			DPRINTF("\nThe last name is %s", currentStudent->lname);
			DPRINTF("\nThe GPA is %.2f",currentStudent->GPA);
			for(int y = 0; y<5;y++)
			{
				DPRINTF("\nCourse %d ID is %d",y+1,currentStudent->cid[y]);
			}
			return FIFO_no_error;
		}
		currentStudent++;

	}
	DPRINTF("\n[ERROR] First Number %s is not found !",temp_str);
	return FIFO_error;

}
FIFO_Buf_status Find_by_cID(FIFO_Buf* fifo)
{
	sInfo* currentStudent = fifo->base;
	char temp_str[30];
	int temp_int;
	int count = 0;
	if(!fifo->base || !fifo->head || !fifo->tail)
	{
		return FIFO_Null;
	}
	if(fifo->count == 0)
	{
		DPRINTF("No Registered Students yet.");
		return FIFO_empty;
	}
	DPRINTF("\nEnter the course ID: ");
	gets(temp_str);
	temp_int = atoi(temp_str);

	for(int i = 0; i<fifo->count;i++)
	{
		for(int z=0; z< 5;z++)
		{
			if(currentStudent->cid[z] == temp_int)
			{
				DPRINTF("\nThe Student Details are : ");
				DPRINTF("\nThe first name is %s", currentStudent->fname);
				DPRINTF("\nThe last name is %s", currentStudent->lname);
				DPRINTF("\nThe GPA is %.2f",currentStudent->GPA);
				DPRINTF("\nThe Roll Number is %d", currentStudent->roll);
				count ++;
			}
		}
		currentStudent++;

	}
	if (count > 0)
	{
		DPRINTF("\n[INFO] Total Number of Students Enrolled: %d.", count);
		return FIFO_no_error;
	}
	else
	{
		DPRINTF("\n[ERROR] Course ID %d is not found", temp_int);
		return FIFO_error;
	}

}

FIFO_Buf_status total_number(FIFO_Buf* fifo)
{
	if(!fifo->base || !fifo->head || !fifo->tail)
	{
		return FIFO_Null;
	}
	if(fifo->count == 0)
	{
		DPRINTF("No Registered Students yet.");
		return FIFO_empty;
	}
	DPRINTF("\n The total number of Students is %d",fifo->count);
	DPRINTF("\n You can add up to 50 Students.");
	DPRINTF("\n You can add %d more Students.", 50-(fifo->count));
	return FIFO_no_error;
}
FIFO_Buf_status view_student(FIFO_Buf* fifo)
{
	sInfo* currentStudent = fifo->base;
	if(!fifo->base || !fifo->head || !fifo->tail)
	{
		return FIFO_Null;
	}
	if(fifo->count == 0)
	{
		DPRINTF("No Registered Students yet.");
		return FIFO_empty;
	}
	DPRINTF("\n=========================================");
	for(int i = 0; i<fifo->count;i++)
	{
		DPRINTF("\n--------------------------------");
		DPRINTF("\nThe Student Details are : ");
		DPRINTF("\nThe first name is %s", currentStudent->fname);
		DPRINTF("\nThe last name is %s", currentStudent->lname);
		DPRINTF("\nThe GPA is %.2f",currentStudent->GPA);
		DPRINTF("\nThe Roll Number is %d", currentStudent->roll);
		for(int y = 0; y<5;y++)
		{
			DPRINTF("\nCourse %d ID is %d",y+1,currentStudent->cid[y]);
		}
		DPRINTF("\n--------------------------------");
		currentStudent++;

	}
	DPRINTF("\n=========================================");
	return FIFO_no_error;
}
FIFO_Buf_status delete_student(FIFO_Buf* fifo)
{
	sInfo* currentStudent = fifo->base;
	int temp_str[30];
	DPRINTF("\nEnter the roll number which you want to delete: ");
	gets(temp_str);
	int temp_int = atoi(temp_str);

	for(int i = 0 ; i<fifo->count ; i++)
	{
		if(currentStudent->roll == temp_int)
		{
			for(int j = i; j < fifo->count -1;j++ )
			{
				buf[j] = buf[j+1];
			}
			fifo->count--;
			return FIFO_no_error;
			DPRINTF("\n[INFO] The Roll Number is removed successfully.");
			DPRINTF("\n")
			break;
		}
		else{
			currentStudent++;
		}
	}
	DPRINTF("[ERROR] The Roll Number %d is not Found.", temp_int);
	return FIFO_error;

}
FIFO_Buf_status update_student(FIFO_Buf* fifo)
{
	sInfo* currentStudent = fifo->base;
	char temp_str[30];
	int temp_int;
	int choice;
	int flag = 0;
	DPRINTF("\nEnter the roll number to update entry : ");
	gets(temp_str);
	temp_int = atoi(temp_str);
	for(int i = 0; i<=fifo->count; i++,currentStudent++)
	{
		if(temp_int == currentStudent->roll)
		{
			flag ++;
			DPRINTF("\nChoose what you need to update from the following.");
			DPRINTF("\n1:First name.");
			DPRINTF("\n2:Last name.");
			DPRINTF("\n3:Roll Number.");
			DPRINTF("\n4:GPA.");
			DPRINTF("\n5:Courses.");
			scanf("%d",&choice);
			switch(choice)
			{
			case 1:
				DPRINTF("\nEnter the new first name: ");
				gets(currentStudent->fname);
				DPRINTF("[INFO] Updated SUCCESSFULLY.");
				break;
			case 2:
				DPRINTF("\nEnter the new last name: ");
				gets(currentStudent->lname);
				DPRINTF("[INFO] Updated SUCCESSFULLY.");
				break;
			case 3:
				DPRINTF("\nEnter the new Roll Number:");
				scanf("%d",&currentStudent->roll);
				DPRINTF("[INFO] Updated SUCCESSFULLY.");
				break;
			case 4:
				DPRINTF("\nEnter the new GPA: ");
				scanf("%f",&currentStudent->GPA);
				DPRINTF("[INFO] Updated SUCCESSFULLY.");
				break;
			case 5:
				DPRINTF("\nEnter the new Courses: ");
				for(int i = 0; i< 5; i++)
				{
					DPRINTF("\nThe new course %d ID is : ", i + 1);
					scanf("%d",&currentStudent->cid[i]);
				}
				DPRINTF("[INFO] Updated SUCCESSFULLY.");
				break;
			default:
				DPRINTF("\nWrong Choice.");
				break;

			}
		}

	}
	if(flag)
	{
		return FIFO_no_error;
	}
	DPRINTF("\n[ERROR] Roll Number not found !");
	return FIFO_error;
}
FIFO_Buf_status FIFo_add_from_file(FIFO_Buf* fifo)
{
	FILE *fptr;
	sInfo* newStudent = fifo->base;
	fptr = fopen("students_data.txt","r");
	char myString [200];
	if(!fifo->base || !fifo->head || !fifo->tail)
	{
		DPRINTF("\n[ERROR] FIFO buffer is not initialized.");
		fclose(fptr);
		return FIFO_Null;
	}
	if(fifo->count == fifo->length)
	{
		printf("\n[ERROR] FIFO buffer is full.");
		fclose(fptr);
		return FIFO_Full;
	}
	if(fptr != NULL)
	{
		while(fgets(myString,100,fptr))
		{
			int read = sscanf(myString,"%d %s %s %f %d %d %d %d %d", &newStudent->roll,newStudent->fname,newStudent->lname,&newStudent->GPA,&newStudent->cid[0],&newStudent->cid[1],&newStudent->cid[2],&newStudent->cid[3],&newStudent->cid[4]);
			//			if(read != 9)
			//			{
			//				DPRINTF("\n[ERROR] Incorrect format in file.");
			//				return FIFO_error;
			//			}
			if(check_roll_number(fifo,newStudent->roll)==1)
			{
				DPRINTF("\n[ERROR] Roll Number %d is taken before.", newStudent->roll);
			}
			else{
				DPRINTF("\n-----------------------------------------");
				DPRINTF("\n Roll number is : %d", newStudent->roll);
				DPRINTF("\n First name is : %s", newStudent->fname);
				DPRINTF("\n Last name is : %s", newStudent->lname);
				DPRINTF("\n GPA is : %.2f", newStudent->GPA);
				for(int i = 0 ; i<5;i++)
				{
					DPRINTF("\n Course %d is : %d", i+1, newStudent->cid[i]);
				}
				DPRINTF("\n[INFO] Student added Successfully.");
				DPRINTF("\n-----------------------------------------");
				newStudent++;
				fifo->count++;
			}

		}
		fclose(fptr);
		return FIFO_no_error;
	}
	else
	{
		DPRINTF("\n[ERROR] Unable to open file.");
		return FIFO_error;
	}

}

