#include <stdio.h>

int main()
{
	float a;
	printf("Enter a number:  \r\n");
	fflush(stdin); fflush(stdout);
	scanf("%f ",&a);
	fflush(stdin); fflush(stdout);
	if (a>0)
		printf("%f is positive.\r\n", a);
	else if (a<0)
		printf("%f is negative.\r\n", a);
	else
		printf("You entered zero.\r\n");
}

