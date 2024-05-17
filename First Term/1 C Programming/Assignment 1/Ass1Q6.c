#include <stdio.h>
int main()
{
	int a,i;
	int sum =0;
	printf("Enter an integer: \r\n");
	fflush(stdin); fflush(stdout);
	scanf("%d",&a);
	for(i=0;i<=a;i++)
	{
		sum+=i;
	}
	printf("Sum = %d",sum);
}