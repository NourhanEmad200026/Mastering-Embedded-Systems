/*
 * ass1q2.c
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */
#include <stdio.h>
int factorial(int num)
{

	if(num!=1){
		return num*factorial(num-1);
	}

}
int main()
{
	int n,x;
	printf("Enter a positive integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	x=factorial(n);
	printf("\n Factorial of %d = %d",n,x);


}
