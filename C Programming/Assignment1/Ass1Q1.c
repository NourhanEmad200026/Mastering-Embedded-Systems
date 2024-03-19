#include <stdio.h>

int main()
{
	int input;
	printf("Enter an integer you want to check: \r\n");
	fflush(stdin);fflush(stdout);
	scanf("%d",&input);
	if(input % 2 == 0)
	{
		printf("%d is even.\r\n",input);
	}
	else
		printf("%d is odd.\r\n",input);
}

