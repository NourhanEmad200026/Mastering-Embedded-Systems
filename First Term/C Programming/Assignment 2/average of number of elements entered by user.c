/*
 * ass1q2.c
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */
#include <stdio.h>

int main()
{
	int n,i;
	float a[100];
	float sum =0.0;
	printf("Enter the numbers of data: \n");
	fflush(stdin); fflush(stdout);
	scanf("%d", &n);
	for(i=0;i<n;i++)
	{
		printf("Enter number: \n");
		fflush(stdin); fflush(stdout);
		scanf("%f",&a[i]);
		sum+=a[i];
	}
	printf("Average = %.2f",sum/n);

}
