/*
 * ass1q2.c
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */
#include <stdio.h>
int main()
{
	char choice;
	float a, b;
	printf("Enter operator either + or - or * or /.\r\n");
	fflush(stdin); fflush(stdout);
	scanf("%c",&choice);
	fflush(stdin); fflush(stdout);
	switch(choice)
	{
	case('+'):
		{
		printf("Enter two operands: \r\n");
		fflush(stdin); fflush(stdout);
		scanf("%f %f",&a,&b);
		printf("%f + %f = %f",a,b,a+b );
		}
	break;
	case('-'):
			{
		printf("Enter two operands: \r\n");
		fflush(stdin); fflush(stdout);
		scanf("%f %f",&a,&b);
		printf("%f - %f = %f",a,b,a-b );
			}
	break;
	case('*'):
			{
		printf("Enter two operands: \r\n");
		fflush(stdin); fflush(stdout);
		scanf("%f %f",&a,&b);
		printf("%f * %f = %f",a,b,a*b );
			}
	break;
	case('/'):
			{
		printf("Enter two operands: \r\n");
		fflush(stdin); fflush(stdout);
		scanf("%f %f",&a,&b);
		printf("%f / %f = %f",a,b,a/b );
			}
	break;
	}

}
