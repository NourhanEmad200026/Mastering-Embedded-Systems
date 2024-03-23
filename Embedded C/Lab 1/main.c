#include "uart.h"

unsigned char string_buffer[100] = "Learn-in-depth: Nourhan Emad Ali" ;

void main(void)
{
	UART_SEND_STRING(string_buffer);
}