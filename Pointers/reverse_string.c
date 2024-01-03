/*
 * main.c
 *
 *  Created on: Jan 3, 2024
 *      Author: nemad
 */
#include <stdio.h>
#include <stdlib.h>
int main()
{
	char str1[50];
	char rev[50];
	char *strr1=str1;
	char *rev1=rev;
	printf("Enter a string: ");
	fflush(stdin); fflush(stdout);
	scanf("%s",str1);
	int i=-1;
	while(*strr1)
	{
		strr1++;
		i++;
	}
	while(i>=0)
	{
		strr1--;
		*rev1=*strr1;
		rev1++;
		--i;
	}
	*rev1='\0';
	printf("Reverse of string is : %s",rev);
}

