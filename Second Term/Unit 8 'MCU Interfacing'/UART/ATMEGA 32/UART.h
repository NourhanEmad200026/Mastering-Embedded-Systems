/*
 * UART.h
 *
 * Created: 8/18/2024 4:45:34 PM
 *  Author: nemad
 */ 


#ifndef UART_H_
#define UART_H_
#define F_CPU 1000000UL 
#include "stdint.h"

#include <avr/io.h>
#include "../../utils.h"

#define Default_Stop '\r'

typedef enum{
	Polling_disable ,
	Polling_enable  
}Polling_Mechanism ;


typedef struct{
	uint16_t Baud_Rate ; //@ref Baud Rate
	uint8_t Parity     ; //@ref Parity Bits
	uint8_t Stop_Bits  ; //@ref Stop Bits
	uint8_t Data_Bits  ; //@ref Data Bits
	uint8_t IRQ_EN     ; //@ref Interrupt Enable
	uint8_t Speed      ; //@ref UART Speed
	void (*IRQ_CallBack)(void) ;
}S_UART_INIT;

/*=====================================================================
======================MACROS CONFIGURATION=============================
=======================================================================
*/
//@ref Baud Rate
#define Baud_Rate_2400      2400
#define Baud_Rate_4800      4800
#define Baud_Rate_9600      9600
#define Baud_Rate_14400     14400
//@ref Parity Bits
#define Parity_Disabled     ((0b00) << UPM0)
#define Parity_Reserved     ((0b01) << UPM0)
#define Parity_Even         ((0b10) << UPM0)
#define Parity_Odd          ((0b11) << UPM0)

//@ref Stop Bits
#define Stop_Bits_0         (0 << USBS)
#define Stop_Bits_1         (1 << USBS)

//@ref Data Bits
#define Data_5Bits          ((0b00) << UCSZ0)
#define Data_6Bits          ((0b01) << UCSZ0)
#define Data_7Bits          ((0b10) << UCSZ0)
#define Data_8Bits          ((0b11) << UCSZ0)
#define Data_9Bits          ((0b11) << UCSZ0)
#define Data_9Bits_Z2       ((0b1)  << UCSZ2)

//@ref UART Speed
#define UART_STD_SPEED      ((0b0) << U2X)
#define UART_FAST_SPEED     ((0b1) << U2X)

//@ref Interrupt Enable
#define IRQ_EN_NONE          0
#define IRQ_EN_TXCIE        ((0b1) << TXCIE)
#define IRQ_EN_RXCIE        ((0b1) << RXCIE)
#define IRQ_EN_TXCIE_RXCIE  (((0b1) << TXCIE) | (((0b1) << RXCIE)))



void UART_INIT (S_UART_INIT * UART_CFG) ;

void UART_TX(uint8_t data ) ;
uint8_t UART_RX(void) ;

void UART_Send_String(uint8_t * str ) ;
void UART_Receive_String(uint8_t * str ) ;

uint8_t UART_Rec_Periodic_Check(uint8_t * pdata) ;
uint8_t UART_RX_NO_Block(void) ;
void UART_TX_NO_Block(uint8_t data) ;
void UART_RX_IRQ_EN(void) ;
void UART_RX_IRQ_DIS(void) ;
void UART_TX_IRQ_EN(void) ;
void UART_TX_IRQ_DIS(void) ;

void UART_SendString_Asynch(uint8_t * str) ;


#endif /* UART_H_ */