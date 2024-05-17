#include "uart.h"
typedef volatile unsigned int vuint32_t ;

#define UARTDR0 *((vuint32_t*)((vuint32_t)0x101F1000))

void UART_SEND_STRING(unsigned char *P_tx_string)
{
	while(*P_tx_string != '\0')
	{
		UARTDR0 = (unsigned int)(*P_tx_string);
		P_tx_string++;
	}
}