/*
 * USART.h
 *
 *  Created on: Sep 16, 2024
 *      Author: nemad
 */

#ifndef INC_USART_H_
#define INC_USART_H_

#include "stm32F103C6.h"
#include "GPIO.h"
#include "RCC.h"

typedef struct
{
	uint8_t                USART_Mode    ; //Specifies Tx/Rx Enable/Disable @ref USART_Mode

	uint32_t               BaudRate      ; //@ref BaudRate

	uint8_t                PayloadLength ; //@ref Payload Length

	uint8_t                Parity        ; //@ref Parity define

	uint8_t                StopBits      ; //@ref Stop Bits define

	uint8_t                FlowCTRL      ; //@ref Flow Control define

	uint8_t                IRQ_Enable    ; //@ref IRQ Enable define

	void(* P_IRQ_CallBack)(void) ;

}UART_Config;




//=============================================================
//======================BAUD RATE CONFIG=======================
//=============================================================
#define USARTDIV(_PCLK_, _BAUD_)              (uint32_t)(_PCLK_/(16 * _BAUD_))
#define USARTDIV_MUL100(_PCLK_, _BAUD_)       (uint32_t)(25 * _PCLK_/(4 * _BAUD_))
#define Mantissa_MUL100(_PCLK_, _BAUD_)       (uint32_t)(USARTDIV(_PCLK_, _BAUD_) * 100)
#define Mantissa(_PCLK_, _BAUD_)              (uint32_t)(USARTDIV(_PCLK_, _BAUD_))
#define DIV_FRACTION(_PCLK_, _BAUD_)          (uint32_t)((((USARTDIV_MUL100(_PCLK_, _BAUD_)) - (Mantissa_MUL100(_PCLK_, _BAUD_))) * 16) / 100)

#define UART_BRR_Register(_PCLK_ , _BAUD_)    ((Mantissa(_PCLK_ , _BAUD_)) << 4) | ((DIV_FRACTION(_PCLK_ , _BAUD_)) & 0xF )





//=============================================================
//================MACROS CONFIG REFERENCE======================
//=============================================================

//@ref USART_Mode
#define UART_Mode_RX                 (uint32_t)(1 << 2)
#define UART_Mode_TX                 (uint32_t)(1 << 3)
#define UART_Mode_TX_RX              (uint32_t)((1 << 2) |(1 << 3))

//@ref BaudRate
#define UART_BaudRate_2400         2400
#define UART_BaudRate_9600         9600
#define UART_BaudRate_19200        19200
#define UART_BaudRate_57600        57600
#define UART_BaudRate_115200       115200
#define UART_BaudRate_230400       230400
#define UART_BaudRate_460800       460800
#define UART_BaudRate_921600       921600
#define UART_BaudRate_2250000      2250000
#define UART_BaudRate_4500000      4500000

//@ref Payload Length

#define UART_Payload_Length_8B     (uint32_t)(0)
#define UART_Payload_Length_9B     (uint32_t)(1 << 12)

//@ref Parity define
#define UART_Parity_NONE           (uint32_t)(0)
#define UART_Parity_EVEN           (uint32_t)(1 << 10)
#define UART_Parity_ODD            (uint32_t)((1 << 9) |(1 << 10))

//@ref Stop Bits define

#define StopBits_half              (uint32_t)(1 << 12)
#define StopBits_1                 (uint32_t)(0)
#define StopBits_1_half            (uint32_t)(3 << 12)
#define StopBits_2                 (uint32_t)(2 << 12)

//@ref Flow Control define
#define UART_FlowCTRL_NONE         (uint32_t)(0)
#define UART_FlowCTRL_RTS          (uint32_t)(1 << 8)
#define UART_FlowCTRL_CTS          (uint32_t)(1 << 9)
#define UART_FlowCTRL_RTS_CTS      (uint32_t)(1 << 8 | 1 << 9)

//@ref IRQ Enable define
#define UART_IRQ_Enable_NONE       (uint32_t)(0)
#define UART_IRQ_Enable_TXE        (uint32_t)(1 << 7)
#define UART_IRQ_Enable_TC         (uint32_t)(1 << 6)
#define UART_IRQ_Enable_RXNEIE     (uint32_t)(1 << 5)
#define UART_IRQ_Enable_PE         (uint32_t)(1 << 8)


enum  Polling_mechanism {
	disable ,
	enable
};
//=============================================================
//===========APIs Supported by MCAL GPIO Driver================
//=============================================================


void MCAL_UART_Init(USART_TypeDef* USARTx , UART_Config * UART_CFG);
void MCAL_UART_DeInit(USART_TypeDef* USARTx);

void MCAL_UART_GPIO_SetPins(USART_TypeDef * USARTx);

void MCAL_UART_SEND_DATA(USART_TypeDef * USARTx, uint16_t * pTX_Buf , enum Polling_mechanism PollingEN);
void MCAL_UART_RECEIVE_DATA(USART_TypeDef * USARTx, uint16_t * pTX_Buf , enum Polling_mechanism PollingEN);

void MCAL_UART_WAIT_TC(USART_TypeDef* USARTx);






#endif /* INC_USART_H_ */

