/*
 * ass1q2.c
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */
#include <stdio.h>

int main()
{
	int a[20];
	int i,n,search;
	printf("Enter no of elements : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	for (i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	printf("\nEnter the elements to be searched for: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&search);
	for(i=0;i<n;i++)
	{
		if(search == a[i])
		{
			printf("\nNumber found at the location %d. ",i+1);
			break;
		}
	}
	if(i==n)
	{
		printf("Element not found\n");
	}

}