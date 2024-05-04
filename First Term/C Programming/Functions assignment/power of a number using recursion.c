/*
 * ass1q2.c
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */
#include <stdio.h>
int power(int base, int exp)
{
	if(exp!=0)
		return (base*power(base,exp-1));
	else
		return 1;
}
int main()
{
	int base,exp;
	printf("Enter base number: \n");
	fflush(stdin); fflush(stdout);
	scanf("%d",&base);
	printf("Enter power number(positive number): \n");
	fflush(stdin); fflush(stdout);
	scanf("%d",&exp);
	fflush(stdin); fflush(stdout);
	printf("%d ^ %d = %d",base,exp,power(base,exp));
}
