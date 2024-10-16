/*
 * UART.c
 *
 * Created: 8/18/2024 4:45:57 PM
 *  Author: nemad
 */ 

#include "UART.h"

static char *  TX_STR ;
static char flag_send = 1;

void UART_INIT (S_UART_INIT * UART_CFG)
{
	UCSRB |= (1<<RXEN) | (1<<TXEN);
	if(UART_CFG->Data_Bits == Data_9Bits)
	{
		UCSRC =(1 << URSEL) |  Data_9Bits ;
		UCSRB |= Data_9Bits_Z2 ;
		}else{
		UCSRC =(1 << URSEL) |  (UART_CFG->Data_Bits) ;
		UCSRB &=~ Data_9Bits_Z2 ;
	}
	UCSRC =(1 << URSEL) |  (UART_CFG->Parity) ;
	UCSRC =(1 << URSEL) |  (UART_CFG->Stop_Bits) ;
	if(UART_CFG->Speed == UART_STD_SPEED)
	{
		uint32_t BAUD = ((F_CPU/(16UL * UART_CFG->Baud_Rate)) - 1) ;
		UBRRH |= (BAUD >> 8) & 0xFF;
		UBRRL |= BAUD & 0xFF ;
		}else{
		UCSRA |= (1 << U2X); 
		uint32_t BAUD = ((F_CPU/(8UL * UART_CFG->Baud_Rate)) - 1) ;
		UBRRH |= (BAUD >> 8) & 0xFF;
		UBRRL |= BAUD & 0xFF;
	}
	

}
void UART_TX(uint8_t data)
{
	while(!(ReadBit(UCSRA , UDRE))) ;
	UDR = data ;
}

uint8_t UART_RX(void) {
	while(!(ReadBit(UCSRA , RXC ))) ;
	return UDR ;
}
void UART_Send_String(uint8_t * str)
{
	char i ;
	for(i = 0 ; i <str[i] ; i++)
	{
		UART_TX(str[i]);
	}
	UART_TX(Default_Stop);
}

void UART_Receive_String(uint8_t * str)
{
	char i  =  0  ;
	str[i] = UART_RX();
	while(str[i] != Default_Stop)     // msh ha3ml while 3ala buff fady aw yekoon enter 
	{
		i++ ;
		str[i] = UART_RX() ;
	}
	str[i] = '\0' ;
	
	
}

uint8_t UART_Rec_Periodic_Check(uint8_t * pdata)
{
	if(ReadBit(UCSRA , RXC))
	{
		*pdata = UDR ;
		return 1 ;
	}
	return 0 ;
}

uint8_t UART_RX_NO_Block(void) 
{
	return UDR ;
}
void UART_TX_NO_Block(uint8_t data) 
{
	UDR = data ;
}
void UART_RX_IRQ_EN(void) 
{
	SetBit(UCSRB , RXCIE) ;
}
void UART_RX_IRQ_DIS(void)
{
	ClearBit(UCSRB, RXCIE) ;
}
void UART_TX_IRQ_EN(void) 
{
	SetBit(UCSRB,TXCIE) ;
}
void UART_TX_IRQ_DIS(void) 
{
	ClearBit(UCSRB,TXCIE) ;
}

void UART_SendString_Asynch(uint8_t * str) 
{
	if(flag_send == 1)
	{
		UART_TX_IRQ_EN() ;
		UART_TX_NO_Block(str[0]) ;
		TX_STR = str ;
		flag_send = 0 ;
	}
}

ISR(USART_TXC_vect)
{
	static uint8_t i = 1 ;
	if(TX_STR[i] != 0)
	{
		UART_TX_NO_Block(TX_STR[i]) ;
		i++ ;
	}else{
		i = 1 ; 
		flag_send = 1 ;
	}
}