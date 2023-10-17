/*
 * ass1q2.c
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */
#include <stdio.h>
#include <string.h>
struct Sstudents{
	char name[10];
	int ID;
	int Grade;
};
int main()
{
	struct Sstudents X[10],tempStudent;
	int i,c;
	for(i=0;i<10;i++)
	{
		printf("Enter name: ");
		fflush(stdout);fflush(stdin);
		scanf("%s",X[i].name);
		printf("\nEnter ID: ");
		fflush(stdout); fflush(stdin);
		scanf("%d",&X[i].ID);
		printf("\nEnter Grade: ");
		fflush(stdout); fflush(stdin);
		scanf("%d",&X[i].Grade);
	}

	for(i=0;i<10;i++)
	{
		printf("\nName: %s\nID: %d\nGrade: %d",X[i].name,X[i].ID,X[i].Grade);
	}
}

