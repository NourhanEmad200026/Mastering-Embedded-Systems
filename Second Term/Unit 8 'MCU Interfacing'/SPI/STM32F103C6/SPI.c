/*
 * SPI.c
 *
 *  Created on: Sep 21, 2024
 *      Author: nemad
 */


#include "SPI.h"
#include "stm32F103C6.h"
#include "GPIO.h"

//=============================================================
//======================Generic Variables======================
//=============================================================


SPI_Config * Global_SPI_Config[2] = {NULL , NULL} ;
SPI_Config Global_SPI_Config1 ;
SPI_Config Global_SPI_Config2 ;

//=============================================================
//======================Generic Macros=========================
//=============================================================
#define   SPI1_INDEX            0
#define   SPI2_INDEX            1
#define   SPI_SR_TXE            ((uint8_t)0x02)
#define   SPI_SR_RXNE           ((uint8_t)0x01)


//=============================================================
//================APIs Functions Definitions===================
//=============================================================


/**=====================================================================
 *Function        : MCAL_SPI_INIT
 *Brief           : Initialize SPIx
 *Parameters[in]  : SPIx -> where x can be (1 or 2)
 *Parameters[in]  : SPI_CFG-> pointer to SPI_Config structure that
  	  	  	  	  	contains the config info for the specified SPI instant
 *Return Value    :None
 *Note            :STM32F103C6 has SPI1 and SPI2
 *=====================================================================
 */
void MCAL_SPI_INIT(SPI_TypeDef * SPIx , SPI_Config * SPI_CFG )
{
	//Safety for registers
	uint16_t tmpreg_CR1 = 0 ;
	uint16_t tmpreg_CR2 = 0 ;

	if(SPIx == SPI1)
	{
		Global_SPI_Config1 = *SPI_CFG ;
		Global_SPI_Config[SPI1_INDEX]  = &Global_SPI_Config1 ;
		RCC_SPI1_CLK_EN() ;

	}else if (SPIx == SPI2)
	{
		Global_SPI_Config2 = *SPI_CFG ;
		Global_SPI_Config[SPI2_INDEX]  = &Global_SPI_Config2 ;
		RCC_SPI2_CLK_EN() ;
	}
	//Enable SPI SPE BIT 6 IN CR1
	tmpreg_CR1 = (0x1U << 6) ;

	//Master or Slave
	tmpreg_CR1 |= SPI_CFG->Device_MDOE ;

	//SPI COMM mode
	tmpreg_CR1 |= SPI_CFG->COMM_MODE ;

	//SPI Frame Format
	tmpreg_CR1 |= SPI_CFG->Frame_Format ;

	//SPI Data Size
	tmpreg_CR1 |= SPI_CFG->Data_Size;

	//SPI CLK POL
	tmpreg_CR1 |= SPI_CFG->CLK_POL ;

	//SPI CLK PHA
	tmpreg_CR1 |= SPI_CFG->CLK_PHA ;

	//=======================NSS=================================
	if(SPI_CFG->NSS == SPI_NSS_HW_MASTER_OP_EN)
	{
		tmpreg_CR2 |= SPI_CFG->NSS ;
	}
	else if (SPI_CFG->NSS == SPI_NSS_HW_MASTER_OP_DIS)
	{
		tmpreg_CR2 &= SPI_CFG->NSS ;

	}
	else {
		tmpreg_CR1 |= SPI_CFG->NSS  ;
	}

	//============================================================

	//SPI Baud Rate
	tmpreg_CR1 |= SPI_CFG->SPI_BRPRE ;

	//IRQ
	if(SPI_CFG->IRQ_Enable != SPI_IRQ_Enable_NONE)
	{
		tmpreg_CR2 |= SPI_CFG->IRQ_Enable ;

		if(SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_Enable ;

		}
		else if (SPIx ==SPI2)
		{
			NVIC_IRQ36_SPI2_Enable ;
		}
	}

	SPIx->CR1 = tmpreg_CR1 ;
	SPIx->CR2 = tmpreg_CR2 ;

}





/**=====================================================================
 *Function        : MCAL_SPI_DeINIT
 *Brief           : DeInitialize SPIx
 *Parameters[in]  : SPIx -> where x can be (1 or 2)
 *Parameters[in]  : SPI_CFG-> pointer to SPI_Config structure that
  	  	  	  	  	contains the config info for the specified SPI instant
 *Return Value    :None
 *Note            :STM32F103C6 has SPI1 and SPI2
 *=====================================================================
 */
void MCAL_SPI_DeINIT(SPI_TypeDef * SPIx )
{
	if(SPIx == SPI1)
	{
		NVIC_IRQ35_SPI1_Disable ;
		RCC_SPI1_CLK_Reset() ;
	}else if(SPIx == SPI2)
	{
		NVIC_IRQ36_SPI2_Disable ;
		RCC_SPI2_CLK_Reset() ;
	}
}
/**=====================================================================
 *Function        : MCAL_SPI_Set_PINS
 *Brief           : Set Pins for SPIx
 *Return Value    :None
 *Note            :STM32F103C6 has SPI1 and SPI2
 *=====================================================================
 */
void MCAL_SPI_Set_PINS(SPI_TypeDef * SPIx )
{
	GPIO_PinCFG_T PIN_CFG ;
	if(SPIx == SPI1)
	{
		//PA4    SPI1 NSS
		//PA5    SPI1 SCK
		//PA6    SPI1 MISO
		//PA7    SPI1 MOSI
		if(Global_SPI_Config[SPI1_INDEX]->Device_MDOE == SPI_Device_Mode_MASTER)
		{
			//PA4 : NSS
			switch(Global_SPI_Config[SPI1_INDEX]->NSS)
			{
			case SPI_NSS_HW_MASTER_OP_DIS :

				PIN_CFG.GPIO_PinNumber = GPIO_PIN_4 ;
				PIN_CFG.GPIO_MODE = GPIO_MODE_Input_Flo ;
				MCAL_GPIO_Init(GPIOA, &PIN_CFG) ;

				break ;

			case SPI_NSS_HW_MASTER_OP_EN :

				PIN_CFG.GPIO_PinNumber = GPIO_PIN_4 ;
				PIN_CFG.GPIO_MODE = GPIO_MODE_Output_AF_PP ;
				PIN_CFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
				MCAL_GPIO_Init(GPIOA, &PIN_CFG) ;

				break ;
			}
			//PA5 SPI1 SCK
			PIN_CFG.GPIO_PinNumber = GPIO_PIN_5 ;
			PIN_CFG.GPIO_MODE = GPIO_MODE_Output_AF_PP ;
			PIN_CFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOA, &PIN_CFG) ;

			//PA6 SPI MISO
			PIN_CFG.GPIO_PinNumber = GPIO_PIN_6 ;
			PIN_CFG.GPIO_MODE = GPIO_MODE_Input_Flo ;
			MCAL_GPIO_Init(GPIOA, &PIN_CFG) ;

			//PA7 SPI MOSI
			PIN_CFG.GPIO_PinNumber = GPIO_PIN_7 ;
			PIN_CFG.GPIO_MODE = GPIO_MODE_Output_AF_PP ;
			PIN_CFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOA, &PIN_CFG) ;

		}
		else //Slave
		{
			//PA4 : NSS
			if(Global_SPI_Config[SPI1_INDEX]->NSS == SPI_NSS_HW_SLAVE)
			{
				PIN_CFG.GPIO_PinNumber = GPIO_PIN_4 ;
				PIN_CFG.GPIO_MODE = GPIO_MODE_Input_Flo ;
				MCAL_GPIO_Init(GPIOA, &PIN_CFG) ;
			}

			//PA5 : SPI1 SCK
			PIN_CFG.GPIO_PinNumber = GPIO_PIN_5 ;
			PIN_CFG.GPIO_MODE = GPIO_MODE_Input_Flo ;
			MCAL_GPIO_Init(GPIOA, &PIN_CFG) ;

			//PA6 : SPI1 MISO
			PIN_CFG.GPIO_PinNumber = GPIO_PIN_6 ;
			PIN_CFG.GPIO_MODE = GPIO_MODE_Output_AF_PP ;
			PIN_CFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOA, &PIN_CFG) ;

			//PA7 : SPI1 MOSI
			PIN_CFG.GPIO_PinNumber = GPIO_PIN_7 ;
			PIN_CFG.GPIO_MODE = GPIO_MODE_Input_Flo ;
			MCAL_GPIO_Init(GPIOA, &PIN_CFG) ;
		}

	}
	else if (SPIx == SPI2)
	{
		//PB12    SPI2 NSS
		//PB13    SPI2 SCK
		//PB14    SPI2 MISO
		//PB15    SPI2 MOSI
		if(Global_SPI_Config[SPI2_INDEX]->Device_MDOE == SPI_Device_Mode_MASTER)
		{
			//PB12 : NSS
			switch(Global_SPI_Config[SPI2_INDEX]->NSS)
			{
			case SPI_NSS_HW_MASTER_OP_DIS :

				PIN_CFG.GPIO_PinNumber = GPIO_PIN_12 ;
				PIN_CFG.GPIO_MODE = GPIO_MODE_Input_Flo ;
				MCAL_GPIO_Init(GPIOB, &PIN_CFG) ;

				break ;

			case SPI_NSS_HW_MASTER_OP_EN :

				PIN_CFG.GPIO_PinNumber = GPIO_PIN_12 ;
				PIN_CFG.GPIO_MODE = GPIO_MODE_Output_AF_PP ;
				PIN_CFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
				MCAL_GPIO_Init(GPIOB, &PIN_CFG) ;

				break ;
			}
			//PB13 SPI2 SCK
			PIN_CFG.GPIO_PinNumber = GPIO_PIN_13 ;
			PIN_CFG.GPIO_MODE = GPIO_MODE_Output_AF_PP ;
			PIN_CFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOB, &PIN_CFG) ;

			//PB14 SPI MISO
			PIN_CFG.GPIO_PinNumber = GPIO_PIN_14 ;
			PIN_CFG.GPIO_MODE = GPIO_MODE_Input_Flo ;
			MCAL_GPIO_Init(GPIOB, &PIN_CFG) ;

			//PB15 SPI MOSI
			PIN_CFG.GPIO_PinNumber = GPIO_PIN_15 ;
			PIN_CFG.GPIO_MODE = GPIO_MODE_Output_AF_PP ;
			PIN_CFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOB, &PIN_CFG) ;

		}
		else //Slave
		{
			//PB12    SPI2 NSS
			//PB13    SPI2 SCK
			//PB14    SPI2 MISO
			//PB15    SPI2 MOSI
			if(Global_SPI_Config[SPI2_INDEX]->NSS == SPI_NSS_HW_SLAVE)
			{
				PIN_CFG.GPIO_PinNumber = GPIO_PIN_12 ;
				PIN_CFG.GPIO_MODE = GPIO_MODE_Input_Flo ;
				MCAL_GPIO_Init(GPIOB, &PIN_CFG) ;
			}

			//PB13 : SPI2 SCK
			PIN_CFG.GPIO_PinNumber = GPIO_PIN_13 ;
			PIN_CFG.GPIO_MODE = GPIO_MODE_Input_Flo ;
			MCAL_GPIO_Init(GPIOB, &PIN_CFG) ;

			//PB14 : SPI2 MISO
			PIN_CFG.GPIO_PinNumber = GPIO_PIN_14 ;
			PIN_CFG.GPIO_MODE = GPIO_MODE_Output_AF_PP ;
			PIN_CFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
			MCAL_GPIO_Init(GPIOB, &PIN_CFG) ;

			//PB15 : SPI2 MOSI
			PIN_CFG.GPIO_PinNumber = GPIO_PIN_15 ;
			PIN_CFG.GPIO_MODE = GPIO_MODE_Input_Flo ;
			MCAL_GPIO_Init(GPIOB, &PIN_CFG) ;
		}


	}
}
/**=====================================================================
 *Function        : MCAL_SPI_TX
 *Brief           : Send buffer on SPI
 *Parameters[in]  : SPIx -> where x can be (1 or 2)
 *Parameters[in]  : pTX_Buff
 *Parameters[in]  : Polling_MECH Enable polling or disable it
 *Return Value    :None
 *Note            :STM32F103C6 has SPI1 and SPI2
 *=====================================================================
 */
void MCAL_SPI_TX(SPI_TypeDef * SPIx , uint16_t * pTX_Buff , enum Polling_MECH POLLING)
{
	if(POLLING == polling_enable)
	{
		while(!((SPIx)->SR & SPI_SR_TXE)) ;
	}
	SPIx->DR = *pTX_Buff ;
}

/**=====================================================================
 *Function        : MCAL_SPI_RX
 *Brief           : Receive buffer on SPI
 *Parameters[in]  : SPIx -> where x can be (1 or 2)
 *Parameters[in]  : pTX_Buff
 *Parameters[in]  : Polling_MECH Enable polling or disable it
 *Return Value    :None
 *Note            :STM32F103C6 has SPI1 and SPI2
 *=====================================================================
 */
void MCAL_SPI_RX(SPI_TypeDef * SPIx , uint16_t * pRX_Buff , enum Polling_MECH POLLING)
{
	if(POLLING == polling_enable)
	{
		while(!((SPIx)->SR & SPI_SR_RXNE)) ;
	}
	*pRX_Buff = SPIx->DR  ;

}

/**=====================================================================
 *Function        : MCAL_SPI_RX_TX
 *Brief           : Receive & Send buffer on SPI
 *Parameters[in]  : SPIx -> where x can be (1 or 2)
 *Parameters[in]  : pTX_Buff
 *Parameters[in]  : Polling_MECH Enable polling or disable it
 *Return Value    :None
 *Note            :STM32F103C6 has SPI1 and SPI2
 *=====================================================================
 */
void MCAL_SPI_RX_TX(SPI_TypeDef * SPIx , uint16_t * p_TX_RX_Buff , enum Polling_MECH POLLING)
{
	if(POLLING == polling_enable)
		while(!((SPIx)->SR & SPI_SR_TXE)) ;
	SPIx->DR = *p_TX_RX_Buff ;


	if(POLLING == polling_enable)
		while(!((SPIx)->SR & SPI_SR_RXNE)) ;
	*p_TX_RX_Buff = SPIx->DR  ;

}



//=============================================================
//=================IRQ Functions Definitions===================
//=============================================================


void	SPI1_IRQHandler (void)
{
	struct S_IRQ_SRC IRQ_SRC ;

	IRQ_SRC.TXE  = ((SPI1->SR & (1 << 1)) >> 1) ;
	IRQ_SRC.RXNE = ((SPI1->SR & (1 << 0)) >> 0) ;
	IRQ_SRC.ERRI = ((SPI1->SR & (1 << 4)) >> 4) ;

	Global_SPI_Config[SPI1_INDEX] -> P_IRQ_CallBack(IRQ_SRC) ;

}
void	SPI2_IRQHandler (void)
{
	struct S_IRQ_SRC IRQ_SRC ;
	IRQ_SRC.TXE  = ((SPI1->SR & (1 << 1)) >> 1) ;
	IRQ_SRC.RXNE = ((SPI1->SR & (1 << 0)) >> 0) ;
	IRQ_SRC.ERRI = ((SPI1->SR & (1 << 4)) >> 4) ;

	Global_SPI_Config[SPI2_INDEX] -> P_IRQ_CallBack(IRQ_SRC) ;
}












