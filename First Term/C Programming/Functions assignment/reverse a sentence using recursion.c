/*
 * ass1q2.c
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */
#include <stdio.h>
void reverse()
{
	char c ;
	scanf("%c",&c);
	if(c!='\n')
	{
		reverse();
		printf("%c",c);
	}
}
int main()
{
	printf("Enter a sentence: ");
	fflush(stdin); fflush(stdout);
	reverse();
}
