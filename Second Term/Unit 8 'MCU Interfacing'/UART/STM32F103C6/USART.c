/*
 * USART.c
 *
 *  Created on: Sep 16, 2024
 *      Author: nemad
 */


#include "USART.h"
//=============================================================
//======================Generic Functions======================
//=============================================================
int get_usart_index(USART_TypeDef* USARTx ){
	if(USARTx == USART1)
	{
		return 0;
	}
	else if(USARTx == USART2)
	{
		return 1 ;
	}
	else if(USARTx == USART3)
	{
		return 2 ;
	}else {
		return -1 ;
	}
}





//=============================================================
//======================Generic Variables======================
//=============================================================


UART_Config * G_UART_CFG[3]= {NULL , NULL , NULL} ;

//=============================================================
//================APIs Functions Definitions===================
//=============================================================


/**=====================================================================
 *Function        : MCAL_UART_Init
 *Brief           : Init UART (Supports Asynchronous only)
 *Parameters[in]  : USARTx : where x can be (1 ..3 depending on device used)
 *Parameters[in]  : UART_CFG: All Uart configurations
 *Return Value    : None
 *Note            : Support Asynchronous mode and clock 8 MHz
 *=====================================================================
 */
void MCAL_UART_Init(USART_TypeDef* USARTx , UART_Config * UART_CFG)
{
	int usart_index = get_usart_index(USARTx) ;

	G_UART_CFG[usart_index] = UART_CFG ;
	uint32_t PCLK ,BRR ;

	//enable clk
	switch (usart_index) {
	case 0:
		RCC_USART1_CLK_EN();
		break;
	case 1:
		RCC_USART2_CLK_EN();
		break;
	case 2:
		RCC_USART3_CLK_EN();
		break;
	default:
		// Handle error: invalid index
		return;
	}
	//Enable Uart module
	USARTx->CR1 |= (1 << 13);

	//Enable TX and Rx
	USARTx->CR1 |= UART_CFG->USART_Mode ;

	//Payload width
	USARTx->CR1 |= UART_CFG->PayloadLength ;

	//Parity Bits
	USARTx->CR1 |= UART_CFG->Parity ;

	//Stop bits
	USARTx->CR1 |= UART_CFG->StopBits ;

	//Flow Control
	USARTx->CR1 |= UART_CFG->FlowCTRL ;

	//Baud Rate
	if(USARTx == USART1)
	{
		PCLK = MCAL_RCC_GetPCLK2_Freq() ;
	}
	else
	{
		PCLK = MCAL_RCC_GetPCLK1_Freq() ;
	}

	BRR = UART_BRR_Register(PCLK , UART_CFG->BaudRate);
	USARTx->BRR = BRR ;

	//Ennable/Disable Interrupts
	if(UART_CFG->IRQ_Enable != UART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |= (UART_CFG->IRQ_Enable) ;

		if(USARTx == USART1)
		{
			NVIC_IRQ37_USART1_Enable ;
		}
		else if(USARTx == USART2)
		{
			NVIC_IRQ38_USART2_Enable ;
		}
		else if(USARTx == USART3)
		{
			NVIC_IRQ39_USART3_Enable ;
		}
	}


}
/**=====================================================================
 *Function        : MCAL_UART_DeInit
 *Brief           : DeInit UART (Supports Asynchronous only)
 *Parameters[in]  : USARTx : where x can be (1 ..3 depending on device used)
 *Return Value    : None
 *Note            : Support Asynchronous mode and clock 8 MHz
 *=====================================================================
 */
void MCAL_UART_DeInit(USART_TypeDef* USARTx)
{
	int usart_index = get_usart_index(USARTx) ;

	switch (usart_index) {
	case 0:
		RCC_USART1_CLK_Reset();
		NVIC_IRQ37_USART1_Disable ;
		break;
	case 1:
		RCC_USART2_CLK_Reset();
		NVIC_IRQ38_USART2_Disable;
		break;
	case 2:
		RCC_USART3_CLK_Reset();
		NVIC_IRQ39_USART3_Disable;
		break;
	}

	// Clear the global configuration pointer
	G_UART_CFG[usart_index] = NULL;

}
/**=====================================================================
 *Function        : MCAL_UART_GPIO_SetPins
 *Brief           : DeInit UART (Supports Asynchronous only)
 *Parameters[in]  : USARTx : where x can be (1 ..3 depending on device used)
 *Return Value    : None
 *Note            : Support Asynchronous mode and clock 8 MHz
 *=====================================================================
 */
void MCAL_UART_GPIO_SetPins(USART_TypeDef * USARTx)
{
	int usart_index = get_usart_index(USARTx) ;
	GPIO_PinCFG_T PINCFG ;
	switch(usart_index)
	{
	case 0:
		//PA9  TX
		//PA10 RX
		//PA11 CTS
		//PA12 RTS

		//PA9 TX
		PINCFG.GPIO_PinNumber = GPIO_PIN_9 ;
		PINCFG.GPIO_MODE = GPIO_MODE_Output_AF_PP ;
		PINCFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOA, &PINCFG) ;

		//PA10 RX
		PINCFG.GPIO_PinNumber = GPIO_PIN_10 ;
		PINCFG.GPIO_MODE = GPIO_MODE_AF_Input ;
		MCAL_GPIO_Init(GPIOA, &PINCFG) ;

		if(G_UART_CFG[usart_index]->FlowCTRL == UART_FlowCTRL_CTS ||G_UART_CFG[usart_index]->FlowCTRL == UART_FlowCTRL_RTS_CTS )
		{
			PINCFG.GPIO_PinNumber = GPIO_PIN_11 ;
			PINCFG.GPIO_MODE = GPIO_MODE_Output_AF_PP ;
			PINCFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOA, &PINCFG) ;
		}
		if(G_UART_CFG[usart_index]->FlowCTRL == UART_FlowCTRL_RTS ||G_UART_CFG[usart_index]->FlowCTRL == UART_FlowCTRL_RTS_CTS )
		{
			PINCFG.GPIO_PinNumber = GPIO_PIN_12 ;
			PINCFG.GPIO_MODE = GPIO_MODE_Output_AF_PP ;
			PINCFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOA, &PINCFG) ;
		}
		break ;

	case 1 :
		//PA2  TX
		//PA3  RX
		//PA0  CTS
		//PA1  RTS

		//PA2 TX
		PINCFG.GPIO_PinNumber = GPIO_PIN_2 ;
		PINCFG.GPIO_MODE = GPIO_MODE_Output_AF_PP ;
		PINCFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOA, &PINCFG) ;

		//PA10 RX
		PINCFG.GPIO_PinNumber = GPIO_PIN_3 ;
		PINCFG.GPIO_MODE = GPIO_MODE_AF_Input ;
		MCAL_GPIO_Init(GPIOA, &PINCFG) ;

		if(G_UART_CFG[usart_index]->FlowCTRL == UART_FlowCTRL_CTS ||G_UART_CFG[usart_index]->FlowCTRL == UART_FlowCTRL_RTS_CTS )
		{
			PINCFG.GPIO_PinNumber = GPIO_PIN_0 ;
			PINCFG.GPIO_MODE = GPIO_MODE_Output_AF_PP ;
			PINCFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOA, &PINCFG) ;
		}
		if(G_UART_CFG[usart_index]->FlowCTRL == UART_FlowCTRL_RTS ||G_UART_CFG[usart_index]->FlowCTRL == UART_FlowCTRL_RTS_CTS )
		{
			PINCFG.GPIO_PinNumber = GPIO_PIN_1 ;
			PINCFG.GPIO_MODE = GPIO_MODE_Output_AF_PP ;
			PINCFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOA, &PINCFG) ;
		}
		break ;
	case 2:

		//PB10  TX
		//PB11 RX
		//PB13 CTS
		//PB14 RTS

		//PB10 TX
		PINCFG.GPIO_PinNumber = GPIO_PIN_10 ;
		PINCFG.GPIO_MODE = GPIO_MODE_Output_AF_PP ;
		PINCFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOB, &PINCFG) ;

		//PB11 RX
		PINCFG.GPIO_PinNumber = GPIO_PIN_11 ;
		PINCFG.GPIO_MODE = GPIO_MODE_AF_Input ;
		MCAL_GPIO_Init(GPIOB, &PINCFG) ;

		if(G_UART_CFG[usart_index]->FlowCTRL == UART_FlowCTRL_CTS ||G_UART_CFG[usart_index]->FlowCTRL == UART_FlowCTRL_RTS_CTS )
		{
			PINCFG.GPIO_PinNumber = GPIO_PIN_13 ;
			PINCFG.GPIO_MODE = GPIO_MODE_Output_AF_PP ;
			PINCFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOB, &PINCFG) ;
		}
		if(G_UART_CFG[usart_index]->FlowCTRL == UART_FlowCTRL_RTS ||G_UART_CFG[usart_index]->FlowCTRL == UART_FlowCTRL_RTS_CTS )
		{
			PINCFG.GPIO_PinNumber = GPIO_PIN_14 ;
			PINCFG.GPIO_MODE = GPIO_MODE_Output_AF_PP ;
			PINCFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOB, &PINCFG) ;
		}
		break ;

	}
}
/**=====================================================================
 *Function        : MCAL_UART_SEND_DATA
 *Brief           : Send Buffer on UART
 *Parameters[in]  : USARTx : where x can be (1 ..3 depending on device used)
 *Parameters[in]  : pTx_Buf Buffer
 *Parameters[in]  : PollingEn Enable polling or disable it
 *Return Value    : None
 *Note            :
 *=====================================================================
 */
void MCAL_UART_SEND_DATA(USART_TypeDef * USARTx, uint16_t * pTX_Buf , enum Polling_mechanism PollingEN)
{
	int usart_index  = get_usart_index(USARTx) ;
	// wait till TXE is set
	if(PollingEN == enable)
	{
		while(! (USARTx->SR & 1 << 7)) ;
	}

	//check the USART word length

	if(G_UART_CFG[usart_index]->PayloadLength == UART_Payload_Length_9B)
	{
		USARTx->DR = (*pTX_Buf & (uint16_t)0x01FF) ;

	}else
	{
		USARTx->DR = (*pTX_Buf & (uint8_t)0xFF) ;

	}

}
/**=====================================================================
 *Function        : MCAL_UART_RECEIVE_DATA
 *Brief           : Receive Buffer on UART
 *Parameters[in]  : USARTx : where x can be (1 ..3 depending on device used)
 *Parameters[in]  : pTx_Buf Buffer
 *Parameters[in]  : PollingEn Enable polling or disable it
 *Return Value    : None
 *Note            :
 *=====================================================================
 */
void MCAL_UART_RECEIVE_DATA(USART_TypeDef * USARTx, uint16_t * pTX_Buf , enum Polling_mechanism PollingEN)
{
	int usart_index = get_usart_index(USARTx) ;

	if(PollingEN == enable)
	{
		while (! (USARTx->SR & 1 << 5));
	}
	if(G_UART_CFG[usart_index]->PayloadLength == UART_Payload_Length_9B)
	{

		if(G_UART_CFG[usart_index]->Parity == UART_Parity_NONE)
		{
			*((uint16_t*)pTX_Buf)  = USARTx->DR ;
		}
		else{
			*((uint16_t*)pTX_Buf)  = ( USARTx->DR & (uint8_t)0xFF) ;

		}
	}
	else{

		if(G_UART_CFG[usart_index]->Parity == UART_Parity_NONE)
		{
			*((uint16_t*)pTX_Buf)  = (USARTx->DR & (uint8_t)0xFF) ;
		}
		else{
			*((uint16_t*)pTX_Buf)  = ( USARTx->DR & (uint8_t)0x7F) ;

		}

	}

}
void MCAL_UART_WAIT_TC(USART_TypeDef* USARTx)
{
	while(!(USARTx->SR & 1 << 6)) ;
}




//=============================================================
//=============================ISR=============================
//=============================================================




void USART1_IRQHandler (void)
{
	G_UART_CFG[0]->P_IRQ_CallBack() ;

}
void USART2_IRQHandler(void)
{
	G_UART_CFG[1]->P_IRQ_CallBack() ;

}
void USART3_IRQHandler(void)
{
	G_UART_CFG[2]->P_IRQ_CallBack() ;

}







