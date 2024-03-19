#include <stdio.h>

int main()
{
	float a,b,c;
	printf("Enter three numbers:  \r\n");
	fflush(stdin); fflush(stdout);
	scanf("%f %f %f ",&a, &b ,&c);
	if(a>b)
	{
		if(a>c)
		{
			printf("Largest number = %f.\r\n",a);
		}

	}
	else if (b>c)
	{
		if(b>a)
		{
			printf("Largest number = %f. \r\n", b);
		}
	}
	else
		printf("Largest number = %f. \r\n", c);
}
