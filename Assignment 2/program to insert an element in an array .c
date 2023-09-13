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
	int n,i,b,location;
	printf("Enter no of elements : \n");
	fflush(stdout); fflush(stdin);
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		a[i]=i+1;
		printf("%d ",a[i]);
	}
	printf("\nEtnter the element to be inserted : \n");
	fflush(stdin); fflush(stdout);
	scanf("%d",&b);

	printf("\nEtnter the location to be inserted : \n");
	fflush(stdin); fflush(stdout);
	scanf("%d",&location);

	for(i=n;i>=location;i--)
	{
		a[i]=a[i-1];
	}
	n++;
	a[location-1]=b;
	for(i=0;i<n;i++)
	{
		printf("%d ",a[i]);
	}
}
