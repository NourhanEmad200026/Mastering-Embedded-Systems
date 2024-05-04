/*
 * ass1q2.c
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */
#include <stdio.h>
#include <string.h>

int main()
{
	char a[100],temp;
	int i=0,j=0;
	printf("Enter a string: ");
	fflush(stdin); fflush(stdout);
	gets(a);
	j=strlen(a)-1;
	while(i<j)
	{
		temp=a[i];
		a[i]=a[j];
		a[j]=temp;
		i++;
		j--;
	}
	printf("\nReverse string is: %s",a);
}
