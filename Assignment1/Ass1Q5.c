#include <stdio.h>
int main()
{
	char c;
	printf("Enter a character : \r\n");
	fflush(stdin); fflush(stdout);
	scanf("%c", &c);
	if ((c >='a' &&c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		printf("%c is an alphabet.\r\n",c);
	}
	else
		printf("%c is not an alphabet.\r\n", c);
}
