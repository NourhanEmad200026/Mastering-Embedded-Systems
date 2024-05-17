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
	printf("Enter a character to find frequency: ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&ch);
	for(i=0;a[i]!='\0';i++)
	{
		if(ch==a[i])
			count++;
	}
	printf("\nFrequency of %c = %d",ch,count);
}
