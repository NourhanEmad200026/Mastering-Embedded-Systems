/*
 * ass1q2.c
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */
#include <stdio.h>

int main()
{
	int i,j;
	float a[2][2];
	float b[2][2];
	float c[2][2];
	printf("Enter the elements of the 1st matrix: \n");
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			printf("Enter a[%d][%d]\n", i,j);
			fflush(stdin);fflush(stdout);
			scanf("%f",&a[i][j]);
		}
	}
	printf("Enter the elements of the 2nd matrix: \n");
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			printf("Enter b[%d][%d]\n", i,j);
			fflush(stdin);fflush(stdout);
			scanf("%f",&b[i][j]);
		}
	}
	for (i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			c[i][j]=a[i][j]+b[i][j];
		}
	}
	printf("Sum of matrix is: \n");
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			printf("%.1f  ",c[i][j]);
			if(j==1){
				printf("\n");
			}
		}
	}
}
