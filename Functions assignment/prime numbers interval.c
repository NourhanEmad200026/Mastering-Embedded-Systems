/*
 * ass1q2.c
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */
#include <stdio.h>
int check_prime(int num);
int main()
{
	int n1,n2,i,flag;
	printf("Enter two numbers(intervals):");
	fflush(stdin); fflush(stdout);
	scanf("%d %d ",&n1,&n2);
	printf("Prime numbers between %d and %d are:  ",n1,n2);
	for(i=n1+1;i<n2;++i)
	{
		flag=check_prime(i);
		if(flag==0)
			printf("%d ",i);
	}
}
int check_prime(int num)
{
	int flag =0;
	int j;
	int x=num/2;
	for(j=2;j<=x;++j)
	{
		if(num%j==0)
		{
			flag=1;
			break;
		}
	}
	return flag;
}
