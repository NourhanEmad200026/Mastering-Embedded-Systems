/*
 * I2C.c
 *
 *  Created on: Oct 6, 2024
 *      Author: nemad
 */
#include "I2C.h"


//=============================================================
//======================Generic Variables======================
//=============================================================

I2C_Init_T Global_I2C_CFG[2] = {NULL , NULL} ;



//=============================================================
//======================Generic Macros=========================
//=============================================================
#define I2C1_Index                    0
#define I2C2_Index                    1


//=============================================================
//======================Generic Functions======================
//=============================================================
void I2C_Generate_Start(I2C_TypeDef * I2Cx ,Functional_State State , Start_Condition Start)
{
	if(Start != repeated_Start)
	{
		//check if the bus is idle or not
		while(I2C_Get_Flag_Status(I2Cx, I2C_Flag_Busy));
	}
	if(State != Disable)
	{
		I2Cx->CR1 |= I2C_CR1_START ;
	}else{
		I2Cx->CR1 &=~ I2C_CR1_START ;
	}
}


Flag_Status I2C_Get_Flag_Status(I2C_TypeDef * I2Cx , Flag Status )
{
	volatile uint32_t dummyRead ;
	Flag_Status bitstatus = Reset ;
	uint32_t flag1 = 0 , flag2 = 0 , lastEvent = 0 ;
	switch (Status)
	{
	case I2C_Flag_Busy :
		if((I2Cx->SR2) & (I2C_SR2_BUSY)){
			bitstatus = Set ;
		}
		else
		{
			bitstatus = Reset ;
		}
		break ;
	case EV5 :
		if((I2Cx->SR1) & I2C_SR1_SB)
		{
			bitstatus = Set ;
		}else{
			bitstatus = Reset ;
		}
		break ;
	case EV6 :
		if((I2Cx->SR1) & I2C_SR1_ADDR)
		{
			bitstatus = Set ;
		}else{
			bitstatus = Reset ;
		}
		dummyRead = I2Cx->SR2 ;
		break ;

	case MASTER_BYTE_TRANSMITTING :
		flag1 = I2Cx->SR1 ;
		flag2 = I2Cx->SR2 ;
		flag2 = flag2 << 16 ;
		lastEvent = (flag1 | flag2) & ((uint32_t)0x00FFFFFF) ;
		if((lastEvent & Status) == Status)
		{
			bitstatus = Set ;
		}else{
			bitstatus = Reset ;
		}
		break ;
	case EV8_1:
	case EV8 :
		if((I2Cx->SR1) & (I2C_SR1_TXE))
		{
			bitstatus = Set ;
		}
		else {
			bitstatus = Reset ;
		}
		break ;
	case EV7 :
		if((I2Cx->SR1) & I2C_SR1_RXNE)
		{
			bitstatus = Set ;
		}else {
			bitstatus = Reset ;
		}
		break ;


	}
	return bitstatus ;
}


void I2C_SendAddress(I2C_TypeDef * I2Cx  , uint16_t Address , I2C_Direction Direction)
{
	uint8_t index = I2Cx == I2C1 ? I2C1_Index :I2C2_Index ;
	if(Global_I2C_CFG[index].I2C_Device_ADD.I2C_Address_slave_mode== I2C_Slave_7Bit)
	{
		Address = Address << 1;
		if(Direction == I2C_Read)
		{
			Address |= ( 1 << 0 );
		}else {
			Address &=~ (1 << 0)	;
		}
	}
	else {
		//not supported
	}
	I2Cx->DR = Address ;

}

void I2C_Generate_Stop(I2C_TypeDef * I2Cx , Functional_State State)
{
	if(State != Disable)
	{
		I2Cx->CR1 |= I2C_CR1_STOP ;
	}
	else{
		I2Cx->CR1 &=~ I2C_CR1_STOP ;
	}
}

void I2C_ACK_CFG(I2C_TypeDef * I2Cx , Functional_State State)
{
	if(State != Disable)
	{
		I2Cx->CR1 |= I2C_CR1_ACK ;
	}
	else
	{
		I2Cx->CR1 &=~ I2C_CR1_ACK ;
	}
}
void Slave_Status(I2C_TypeDef * I2Cx , Slave_State state)
{
	uint8_t index = I2Cx == I2C1 ? I2C1_Index :I2C2_Index ;
	switch (state)
	{
	case I2C_ERROR_AF :
		if((I2Cx->SR2)  & I2C_SR2_TRA){
			//slave shouldnt send any thing
		}
		break  ;
	case I2C_EV_Stop :
		if((I2Cx->SR2)  & I2C_SR2_TRA){
			Global_I2C_CFG[index].P_Slave_Event_CallBack(I2C_EV_Stop) ;
		}
		break ;

	case I2C_EV_ADD_Match :
		Global_I2C_CFG[index].P_Slave_Event_CallBack(I2C_EV_ADD_Match) ;
		break ;

	case I2C_EV_Data_REQ :
		if(I2Cx->SR2 & ( I2C_SR2_TRA))
		{
			Global_I2C_CFG[index].P_Slave_Event_CallBack(I2C_EV_Data_REQ) ;

		}
		break ;


	case I2C_EV_Data_RCV :
		if(!(I2Cx->SR2 & ( I2C_SR2_TRA)))
		{
			Global_I2C_CFG[index].P_Slave_Event_CallBack(I2C_EV_Data_RCV) ;

		}
		break ;




	}
}


//=============================================================
//================APIs Functions Definitions===================
//=============================================================


/**=====================================================================
 *Function        : MCAL_I2C_Init
 *Brief           : Initialize I2Cx
 *Parameters[in]  : I2Cx -> where x can be (1 or 2)
 *Parameters[in]  : I2C_CFG-> pointer to  I2C_Init_T  structure that
  	  	  	  	  	contains the config info for the specified I2C instant
 *Return Value    : None
 *Note            : None
 *=====================================================================
 */
void MCAL_I2C_Init(I2C_TypeDef * I2Cx , I2C_Init_T * I2C_CFG)
{
	uint16_t tmpreg =0 , freqreg = 0 ;
	uint32_t PCLK1 = 8000000 ;
	uint16_t result =  0 ;

	//Enable RCC CLK
	if(I2Cx == I2C1)
	{
		Global_I2C_CFG[I2C1_Index] = *I2C_CFG ;
		RCC_I2C1_CLK_EN() ;
	}else{
		Global_I2C_CFG[I2C2_Index] = *I2C_CFG ;
		RCC_I2C2_CLK_EN() ;
	}

	if(I2C_CFG->I2C_MODE == I2C_MODE_I2C)
	{

		/*-------------------INIT TIMINGS-----------------*/
		//to configure clk
		//I2C_CR2 FREQ Bit[5:0]
		tmpreg = I2Cx->CR2 ;
		//Clear freq bits
		tmpreg &=~ (I2C_CR2_FREQ) ;
		PCLK1 = MCAL_RCC_GetPCLK1_Freq() ;
		freqreg = (uint16_t)(PCLK1/ 1000000) ;
		tmpreg |= freqreg ;
		I2Cx->CR2 = tmpreg ;
		//• Configure the clock control registers
		//            Thigh = CCR * T PCLK1
		//            SM or FM
		/* Disable I2C peripheral to configure timings */
		I2Cx->CR1 &=~ (I2C_CR1_PE) ;

		tmpreg=0 ;
		/* Configure speed in standard mode */
		if((I2C_CFG->Clk_Speed == I2C_SCLK_STD_50KHz )||(I2C_CFG->Clk_Speed == I2C_SCLK_STD_100KHz))
		{
			//standard mode speed calculation

			// Tclk /2 = CCR * Tpclk1
			// CCR = Tclk /(2* Tpclk1)
			// CCR = Fpclk1 /(2 * I2C clk speed)
			result = (uint16_t)(PCLK1 / (I2C_CFG->Clk_Speed << 1 )) ;
			tmpreg |= result ;

			I2Cx->CCR = tmpreg ;

			//• Configure the rise time register
			I2Cx->TRISE = freqreg + 1 ;

		}else{
			//fast mode not supported
		}

		// I2C CR1 config
		tmpreg = I2Cx->CR1 ;

		tmpreg |= (uint16_t)( I2C_CFG->I2C_ACK_CTRL | I2C_CFG->I2C_GeneralCallback | I2C_CFG->I2C_MODE | I2C_CFG->Stretch_Mode ) ;
		I2Cx->CR1 = tmpreg ;

		/*-------------I2C OAR1 & OAR2 config-----------------*/
		tmpreg =0 ;
		if(I2C_CFG->I2C_Device_ADD.DUAL_EN == 1)
		{
			tmpreg = I2C_OAR2_ENDUAL ;
			tmpreg |= I2C_CFG->I2C_Device_ADD.Secondary_slave_Address << I2C_OAR2_ADD2_Pos ;
			I2Cx->OAR2 = tmpreg ;

		}
		tmpreg = 0 ;
		tmpreg |= I2C_CFG->I2C_Device_ADD.Primary_slave_Address<< 1 ;
		tmpreg |= I2C_CFG->I2C_Device_ADD.I2C_Address_slave_mode    ;
		I2Cx->OAR1 = tmpreg ;
	}
	else{
		//SMBUS not supported
	}

	//Interrupt Mode (Slave mode) //Check callback pointer != NULL
	if(I2C_CFG->P_Slave_Event_CallBack != NULL) // that enable slave IRQ mode
	{
		I2Cx->CR2 |= (I2C_CR2_ITERREN) ;
		I2Cx->CR2 |= (I2C_CR2_ITEVTEN) ;
		I2Cx->CR2 |= (I2C_CR2_ITBUFEN) ;

		if(I2Cx == I2C1 )
		{
			NVIC_IRQ31_I2C1_EV_Enable ;
			NVIC_IRQ32_I2C1_ER_Enable ;
		}else if(I2Cx == I2C2)
		{
			NVIC_IRQ33_I2C2_EV_Enable ;
			NVIC_IRQ34_I2C2_ER_Enable ;
		}
		I2Cx->SR1 = 0 ;
		I2Cx->SR2 = 0 ;
	}


	/*Enable selected I2C peripheral */
	I2Cx->CR1 |= I2C_CR1_PE   ;

}


/**=====================================================================
 *Function        : MCAL_I2C_DeInit
 *Brief           : DeInitialize I2Cx
 *Parameters[in]  : I2Cx -> where x can be (1 or 2)
 *Return Value    : None
 *Note            : None
 *=====================================================================
 */
void MCAL_I2C_DeInit(I2C_TypeDef * I2Cx)
{
	if(I2Cx == I2C1)
	{
		NVIC_IRQ31_I2C1_EV_Disable ;
		NVIC_IRQ32_I2C1_ER_Disable ;
		RCC_I2C1_CLK_Reset() ;
	}
	else if (I2Cx == I2C2)
	{
		NVIC_IRQ33_I2C2_EV_Disable ;
		NVIC_IRQ34_I2C2_ER_Disable ;
		RCC_I2C2_CLK_Reset() ;
	}
}
/**=====================================================================
 *Function        : MCAL_I2C_GPIO_SetPINS
 *Brief           : Set Pins for I2Cx
 *Return Value    :None
 *Note            :STM32F103C6 has I2C1 and I2C2
 *=====================================================================
 */
void MCAL_I2C_GPIO_SetPINS (I2C_TypeDef * I2Cx)
{
	//I2C1 SCL PB6
	//I2C1 SDA PB7


	GPIO_PinCFG_T PINCFG ;
	if (I2Cx == I2C1)
	{
		PINCFG.GPIO_PinNumber = GPIO_PIN_6 ;
		PINCFG.GPIO_MODE = GPIO_MODE_Output_AF_OD ;
		PINCFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOB, &PINCFG) ;

		PINCFG.GPIO_PinNumber = GPIO_PIN_7 ;
		PINCFG.GPIO_MODE = GPIO_MODE_Output_AF_OD ;
		PINCFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOB, &PINCFG) ;
	}
	else if (I2Cx == I2C2)
	{
		//I2C2 SCL PB10
		//I2C2 SDA PB11

		PINCFG.GPIO_PinNumber = GPIO_PIN_10 ;
		PINCFG.GPIO_MODE = GPIO_MODE_Output_AF_OD ;
		PINCFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOB, &PINCFG) ;

		PINCFG.GPIO_PinNumber = GPIO_PIN_11 ;
		PINCFG.GPIO_MODE = GPIO_MODE_Output_AF_OD ;
		PINCFG.GPIO_Output_Speed = GPIO_SPEED_10M ;
		MCAL_GPIO_Init(GPIOB, &PINCFG) ;
	}


}

/**=====================================================================
 *Function        : MCAL_I2C_MASTER_TX
 *Brief           : Master Send data
 *Parameters[in]  : I2Cx -> where x can be (1 or 2)
 *Parameters[in]  : dvc_ADD -> Address of slave to write on
 *Parameters[in]  : dataTX -> buffer of data to write on
 *Parameters[in]  : data_lenght
 *Parameters[in]  : Stop_Condition Stop -> whether to send stop condition or not
 *Parameters[in]  : Start_Condition Start -> whether to send start or repeated start condition
 *Return Value    : None
 *Note            : None
 *=====================================================================
 */
void MCAL_I2C_MASTER_TX(I2C_TypeDef* I2Cx , uint16_t dvc_ADD , uint8_t * dataTX ,uint32_t data_lenght , Stop_Condition Stop , Start_Condition Start )
{
	int i =  0 ;
	// 1. Set the start bit in I2C CR1 register to generate a start condition
	I2C_Generate_Start(I2Cx, Enable, Start) ;

	while(!(I2C_Get_Flag_Status(I2Cx, EV5))) ;

	I2C_SendAddress(I2Cx, dvc_ADD, I2C_Write) ;

	while(!(I2C_Get_Flag_Status(I2Cx, EV6))) ;

	//check that you are master: TRA , BUSY ,MSL in SR2 , TXE flags

	while(!(I2C_Get_Flag_Status(I2Cx, MASTER_BYTE_TRANSMITTING))) ;

	for(i = 0 ; i < data_lenght ; i++)
	{
		I2Cx->DR = dataTX[i] ;

		while(!(I2C_Get_Flag_Status(I2Cx, EV8))) ;

	}

	if(Stop == with_stop)
	{
		I2C_Generate_Stop(I2Cx, Enable) ;

	}
}






/**=====================================================================
 *Function        : MCAL_I2C_MASTER_RX
 *Brief           : Master Receive data
 *Parameters[in]  : I2Cx -> where x can be (1 or 2)
 *Parameters[in]  : dvc_ADD -> Address of slave to read from
 *Parameters[in]  : dataTX -> buffer of data to read from
 *Parameters[in]  : data_lenght
 *Parameters[in]  : Stop_Condition Stop -> whether to send stop condition or not
 *Parameters[in]  : Start_Condition Start -> whether to send start or repeated start condition
 *Return Value    : None
 *Note            : None
 *=====================================================================
 */
void MCAL_I2C_MASTER_RX(I2C_TypeDef* I2Cx , uint16_t dvc_ADD , uint8_t * dataRX ,uint32_t data_lenght , Stop_Condition Stop , Start_Condition Start )
{
	int i = 0 ;
	uint8_t index = I2Cx == I2C1 ? I2C1_Index :I2C2_Index ;

	I2C_Generate_Start(I2Cx, Enable, Start) ;

	while(!(I2C_Get_Flag_Status(I2Cx, EV5))) ;

	I2C_SendAddress(I2Cx, dvc_ADD, I2C_Read) ;

	while(!(I2C_Get_Flag_Status(I2Cx, EV6))) ;

	I2C_ACK_CFG(I2Cx , Enable) ;

	if(data_lenght)
	{
		for(i = data_lenght ; i > 1 ; i--)
		{
			while(!(I2C_Get_Flag_Status(I2Cx, EV7))) ;
			*dataRX = I2Cx->DR ;
			dataRX ++ ;
		}
		I2C_ACK_CFG(I2Cx , Disable) ;
	}
	if(Stop == with_stop)
	{
		I2C_Generate_Stop(I2Cx, Enable) ;
	}
	if(Global_I2C_CFG[index].I2C_ACK_CTRL == I2C_ACK_EN )
	{
		I2C_ACK_CFG(I2Cx , Enable) ;
	}
}







void MCAL_I2C_SLAVE_SEND(I2C_TypeDef* I2Cx , uint8_t data)
{
	I2Cx->DR = data ;
}
uint8_t MCAL_I2C_SLAVE_RECEIVE(I2C_TypeDef* I2Cx )
{
	return (uint8_t) I2Cx->DR ;
}



void I2C1_EV_IRQHandler (void)
{

	volatile uint32_t dummyRead = 0 ;
	I2C_TypeDef * I2Cx = I2C1 ;
	uint32_t temp1, temp2, temp3 ;

	temp1 = I2Cx->CR2 & ( I2C_CR2_ITEVTEN ) ;
	temp2 = I2Cx->CR2 & ( I2C_CR2_ITBUFEN ) ;
	temp3 = I2Cx->SR1 & ( I2C_SR1_STOPF ) ;

	if(temp1 && temp3)
	{
		I2Cx->CR1 |= 0x0000 ;
		Slave_Status(I2Cx, I2C_EV_Stop) ;

	}
	temp3 = I2Cx->SR1 & (I2C_SR1_ADDR)  ;

	if(temp1 && temp3)
	{
		if(I2Cx->SR2 & (I2C_SR2_MSL))
		{

		}else{
			dummyRead = I2Cx->SR1 ;
			dummyRead = I2Cx->SR2 ;
			Slave_Status(I2Cx, I2C_EV_ADD_Match) ;

		}
	}

	temp3 = I2Cx->SR1 & ( I2C_SR1_TXE) ;
	if(temp1 && temp2 && temp3)
	{
		if(I2Cx->SR2 & (I2C_SR2_MSL))
		{

		}else{
			Slave_Status(I2Cx, I2C_EV_Data_REQ) ;

		}
	}
	temp3 = I2Cx->SR1 & ( I2C_SR1_RXNE) ;
	if(temp1 && temp2 && temp3)
	{
		if(I2Cx->SR2 & (I2C_SR2_MSL))
		{

		}else{
			Slave_Status(I2Cx, I2C_EV_Data_RCV) ;

		}
	}

}

void I2C1_ER_IRQHandler (void)
{

}

void I2C2_EV_IRQHandler (void)
{

	volatile uint32_t dummyRead = 0 ;
	I2C_TypeDef * I2Cx = I2C2 ;
	uint32_t temp1, temp2, temp3 ;

	temp1 = I2Cx->CR2 & ( I2C_CR2_ITEVTEN ) ;
	temp2 = I2Cx->CR2 & ( I2C_CR2_ITBUFEN ) ;
	temp3 = I2Cx->SR1 & ( I2C_SR1_STOPF ) ;

	if(temp1 && temp3)
	{
		I2Cx->CR1 |= 0x0000 ;
		Slave_Status(I2Cx, I2C_EV_Stop) ;

	}
	temp3 = I2Cx->SR1 & (I2C_SR1_ADDR)  ;

	if(temp1 && temp3)
	{
		if(I2Cx->SR2 & (I2C_SR2_MSL))
		{

		}else{
			dummyRead = I2Cx->SR1 ;
			dummyRead = I2Cx->SR2 ;
			Slave_Status(I2Cx, I2C_EV_ADD_Match) ;

		}
	}

	temp3 = I2Cx->SR1 & ( I2C_SR1_TXE) ;
	if(temp1 && temp2 && temp3)
	{
		if(I2Cx->SR2 & (I2C_SR2_MSL))
		{

		}else{
			Slave_Status(I2Cx, I2C_EV_Data_REQ) ;

		}
	}
	temp3 = I2Cx->SR1 & ( I2C_SR1_RXNE) ;
	if(temp1 && temp2 && temp3)
	{
		if(I2Cx->SR2 & (I2C_SR2_MSL))
		{

		}else{
			Slave_Status(I2Cx, I2C_EV_Data_RCV) ;

		}
	}

}

void I2C2_ER_IRQHandler (void)
{

}
