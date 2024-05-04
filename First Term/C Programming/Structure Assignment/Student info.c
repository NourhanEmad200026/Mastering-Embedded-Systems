/*
 * ass1q2.c
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */
#include <stdio.h>
#include <string.h>
struct Sstudents{
	char name[25];
	int roll;
	float marks;
};
int main()
{
	struct Sstudents X;
	printf("Enter information of students: \n");

	printf("Enter name: ");
	fflush(stdout);
	scanf("%s",X.name);
	printf("\nEnter roll number: ");
	fflush(stdout);
	scanf("%d",&X.roll);
	fflush(stdout);
	printf("\nEnter marks: ");
	fflush(stdout);
	scanf("%f",&X.marks);
	fflush(stdout);
	printf("\nName: %s\nRoll: %d\nMarks: %.2f",X.name,X.roll,X.marks);

}
