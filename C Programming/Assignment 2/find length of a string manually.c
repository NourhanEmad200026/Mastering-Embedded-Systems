/*
 * ass1q2.c
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */
#include <stdio.h>

int main()
{
	char a[100],ch;
	int i,count=0;
	printf("Enter a string: ");
	fflush(stdin); fflush(stdout);
	gets(a);
	for(i=0;a[i]!='\0';i++)
	{
		count++;
	}
	printf("\nLength of string: %d",count);
}
