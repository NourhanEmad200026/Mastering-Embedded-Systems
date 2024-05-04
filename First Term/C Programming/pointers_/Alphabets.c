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
	char alph[27];
	char *p=alph;
	int i;
	for(i=0;i<27;i++)
	{
		*p= i + 'A';
		p++;
	}
	p=alph;
	for(i=0;i<27;i++)
	{
		printf("%c ",*p+i);
	}
}

