/*
 * ass1q2.c
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */
#include <stdio.h>

int main()
{
	int a[20][20];
	int t[20][20];
	int n,s;
	int i,j;
	printf("Enter no of rows and columns: \n");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&n,&s);
	for(i=0;i<n;i++)
	{
		for(j=0;j<s;j++)
		{
			printf("Enter elements of matrix a[%d][%d]\n",i+1,j+1);
			fflush(stdin); fflush(stdout);
			scanf("%d",&a[i][j]);
		}
	}
	printf("Entered matrix:  \n");
	for(i=0;i<n;i++)
		{
			for(j=0;j<s;j++)
			{
				printf("%d ",a[i][j]);
			}
			printf("\n");
		}
	for(i=0;i<n;i++)
		{
			for(j=0;j<s;j++)
			{
				t[j][i]=a[i][j];
			}
		}
	printf("Transpose of matrix:  \n");
	for(i=0;i<s;i++)
			{
				for(j=0;j<n;j++)
				{
					printf("%d ",t[i][j]);
				}
				printf("\n");
			}
}
