#include <stdio.h>

int main()
{
	char c;
	printf("Enter an alphabet: \r\n");
	fflush(stdin); fflush(stdout);
	scanf("%c",&c);
	if(c == 'a' || c == 'A' || c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'e'|| c == 'E' || c == 'i' || c == 'I')
	{
		printf("%c is a vowel.\r\n", c);
	}
	else
		printf("%c is a consonant.\r\n", c);
}
