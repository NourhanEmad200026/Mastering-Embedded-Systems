/*
 * ass1q2.c
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */
#include <stdio.h>
int main()
{
	int a,i;
	int sum =1;
	printf("Enter an integer: \r\n");
	fflush(stdin); fflush(stdout);
	scanf("%d",&a);
	if(a>0)
	{
		for(i=1;i<=a;i++)
		{
			sum*=i;
		}
		printf("Factorial = %d",sum);
	}
	else if (a<0)
		printf("ERROR!! Factorial of negative number doesn't exist.\r\n");
	else
		printf("ERROR!! Factorial of zero doesn't exist.\r\n");
}
