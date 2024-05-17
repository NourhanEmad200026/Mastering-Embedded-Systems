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
	struct Sstudents X[5],tempStudent;
	int i,c;
	for(i=0;i<5;i++)
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
	printf("\nChoose one of the following to sort the students according to: \n1:Sort then print the list in alphabetical order.\n2:Sort then print the list based on IDs.\n3:Print the students's name with the highest grade.");
	fflush(stdout); fflush(stdin);
	scanf("%d",&c);
	if(c==1){
		for(i=0;i<4;i++)
		{
			for(int j=i+1;j<5;j++)
			{
				if(X[i].name[0]>X[j].name[0])
				{
					tempStudent = X[i];
					X[i]=X[j];
					X[j]=tempStudent;
				}
			}
		}
	}
	else if(c==2)
	{
		for(i=0;i<4;i++)
		{
			for(int j=i+1;j<5;j++)
			{
				if(X[i].ID>X[j].ID)
				{
					tempStudent = X[i];
					X[i]=X[j];
					X[j]=tempStudent;
				}
			}
		}
	}
	else if(c==3)
	{
		for(i=0;i<4;i++)
		{
			for(int j=i+1;j<5;j++)
			{
				if(X[i].Grade>X[j].Grade)
				{
					tempStudent = X[i];
					X[i]=X[j];
					X[j]=tempStudent;
				}
			}
		}
	}
	else
		printf("\nYou entered a wrong choice.");

	for(i=0;i<5;i++)
	{
		printf("\nName: %s\nID: %d\nGrade: %d",X[i].name,X[i].ID,X[i].Grade);
	}
}
