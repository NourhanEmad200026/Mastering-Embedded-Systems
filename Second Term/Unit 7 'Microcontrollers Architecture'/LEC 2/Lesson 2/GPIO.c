/*
 * GPIO.c
 *
 *  Created on: Aug 3, 2024
 *      Author: nemad
 */

#include "GPIO.h"

uint8_t Get_CRLH_Position(uint16_t PinNumber)
{
	switch (PinNumber)
	{
	case GPIO_PIN_0:
		return 0;
		break;
	case GPIO_PIN_1:
		return 4;
		break;
	case GPIO_PIN_2:
		return 8 ;
		break ;
	case GPIO_PIN_3:
		return 12 ;
		break;
	case GPIO_PIN_4:
		return 16 ;
		break;
	case GPIO_PIN_5:
		return 20 ;
		break;
	case GPIO_PIN_6:
		return 24 ;
		break;
	case GPIO_PIN_7:
		return 28 ;
		break;

	case GPIO_PIN_8:
		return 0;
		break;
	case GPIO_PIN_9:
		return 4;
		break;
	case GPIO_PIN_10:
		return 8 ;
		break ;
	case GPIO_PIN_11:
		return 12 ;
		break;
	case GPIO_PIN_12:
		return 16 ;
		break;
	case GPIO_PIN_13:
		return 20 ;
		break;
	case GPIO_PIN_14:
		return 24 ;
		break;
	case GPIO_PIN_15:
		return 28 ;
		break;
	}
	return 0 ;
}






/**=====================================================================
 *Function        : MCAL_GPIO_Init
 *Brief           : Initialize GPIOx Pin y according to the specified
             	 	 parameters in Pin Configurations.
 *Parameters[in]  :GPIOx -> where x can be (A -> E)
 *Parameters[in]  :PIN_CFG-> pointer to GPIO_PinCFG_T structure that
  	  	  	  	  	contains the config info for the specified GPIO Pin
 *Return Value    :None
 *Note            :STM32F103C6 has GPIO A,B,C,D,E Modules
  	  	  	  	  	But LQFP48 has only GPIO A,B Part of C,D
 *=====================================================================
 */
void MCAL_GPIO_Init(GPIO_TypeDef * GPIOx , GPIO_PinCFG_T * PIN_CFG)
{
	//Port configuration register low (GPIOx_CRL) configure pins from 0 - 7
	//Port configuration register high (GPIOx_CRH) configure pins from 8 - 15
	volatile uint32_t * configRegister = NULL;
	uint8_t PIN_CONFIG = 0;

	configRegister = (PIN_CFG->GPIO_PinNumber < GPIO_PIN_8)? &GPIOx->CRL : &GPIOx ->CRH ;

	//clear CNF , MODE
	(*configRegister) &=~ (0xF << Get_CRLH_Position(PIN_CFG->GPIO_PinNumber));

	//if pin is output
	if(PIN_CFG->GPIO_MODE == GPIO_MODE_Output_PP || PIN_CFG->GPIO_MODE == GPIO_MODE_Output_OD || PIN_CFG->GPIO_MODE == GPIO_MODE_Output_AF_PP || PIN_CFG->GPIO_MODE == GPIO_MODE_Output_AF_OD  )
	{
		PIN_CONFIG = (((PIN_CFG->GPIO_MODE - 4) << 2) | ((PIN_CFG->GPIO_Output_Speed) & 0x0F)); //CNF
	}
	//if pin is input
	else
	{
		if((PIN_CFG->GPIO_MODE == GPIO_MODE_Input_Flo) ||( PIN_CFG->GPIO_MODE == GPIO_MODE_Analog))
		{
			PIN_CONFIG = ((((PIN_CFG->GPIO_MODE ) << 2) | 0x0) & 0x0F); //CNF

		}else if(PIN_CFG->GPIO_MODE == GPIO_MODE_AF_Input)
		{
			PIN_CONFIG = (((( GPIO_MODE_Input_Flo ) << 2) | 0x0) & 0x0F); //CNF
		}
		else //PU or PD
		{
			PIN_CONFIG = ((((GPIO_MODE_Input_PU ) << 2) | 0x0) & 0x0F); //CNF
			if(PIN_CFG->GPIO_MODE == GPIO_MODE_Input_PU)
			{
				GPIOx->ODR |= (PIN_CFG->GPIO_PinNumber);
			}
			else{
				GPIOx->ODR &=~ (PIN_CFG->GPIO_PinNumber);
			}
		}
	}
	(*configRegister) |= ( (PIN_CONFIG) << Get_CRLH_Position(PIN_CFG->GPIO_PinNumber));

}



/**=====================================================================
 *Function        : MCAL_GPIO_DeInit
 *Brief           : Reset GPIOx Pin y according to the specified
             	 	 parameters in Pin Configurations.
 *Parameters[in]  : GPIOx -> where x can be (A -> E)
 *Return Value    : None
 *Note            : None
 *=====================================================================
 */
void MCAL_GPIO_DeInit(GPIO_TypeDef * GPIOx)
{
	if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR |=  (1 << 2);
		RCC->APB2RSTR &=~ (1 << 2);
	}
	if(GPIOx == GPIOB)
	{
		RCC->APB2RSTR |=  (1 << 3);
		RCC->APB2RSTR &=~ (1 << 3);
	}
	if(GPIOx == GPIOC)
	{
		RCC->APB2RSTR |=  (1 << 4);
		RCC->APB2RSTR &=~ (1 << 4);
	}
	if(GPIOx == GPIOD)
	{
		RCC->APB2RSTR |=  (1 << 5);
		RCC->APB2RSTR &=~ (1 << 5);
	}
	if(GPIOx == GPIOE)
	{
		RCC->APB2RSTR |=  (1 << 6);
		RCC->APB2RSTR &=~ (1 << 6);
	}
}


/**=====================================================================
 *Function        : MCAL_GPIO_ReadPin
 *Brief           : Read Specific Pin
 *Parameters[in]  : GPIOx -> where x can be (A -> E)
 *Parameters[in]  : PIN_No -> Set Pin number according to
  	  	  	  	  	 @ref GPIO_PINS_define
 *Return Value    : The Input Pin Value (2 values @ref GPIO_Pin_State)
 *Note            : None
 *=====================================================================
 */
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef * GPIOx  , uint16_t PIN_No)
{
	uint8_t bitStatus ;
	if(((GPIOx->IDR) & PIN_No) != (uint32_t)PIN_RESET)
	{
		bitStatus = PIN_SET ;

	}
	else
	{
		bitStatus = PIN_RESET ;
	}
	return bitStatus ;

}


/**=====================================================================
 *Function        : MCAL_GPIO_ReadPort
 *Brief           : Read Specific Port
 *Parameters[in]  : GPIOx -> where x can be (A -> E)
 *Return Value    : The Input Port Value
 *Note            : None
 *=====================================================================
 */
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef * GPIOx )
{
	uint16_t port_value ;
	port_value = (uint16_t)GPIOx->IDR;
	return port_value ;
}



/**=====================================================================
 *Function        : MCAL_GPIO_WritePin
 *Brief           : Write on specific output pin
 *Parameters[in]  : GPIOx -> where x can be (A -> E)
 *Parameters[in]  : PIN_No-> specifies the port bit to be written on
 *Parameters[in]  : value -> Pin Value
 *Return Value    : None
 *Note            : None
 *=====================================================================
 */
void MCAL_GPIO_WritePin(GPIO_TypeDef * GPIOx  , uint16_t PIN_No , uint8_t value)
{
	if(value != PIN_RESET)
	{
		GPIOx->BSRR = PIN_No;
	}
	else
	{
		GPIOx->BRR = PIN_No ;
	}
}

/**=====================================================================
 *Function        : MCAL_GPIO_WritePort
 *Brief           : Write on specific output Port
 *Parameters[in]  : GPIOx -> where x can be (A -> E)
 *Parameters[in]  : value -> the value to be written on
 *Return Value    : None
 *Note            : None
 *=====================================================================
 */
void MCAL_GPIO_WritePort(GPIO_TypeDef * GPIOx  ,  uint16_t value)
{
	GPIOx->ODR = (uint32_t)value;
}


/**=====================================================================
 *Function        : MCAL_GPIO_TogglePin
 *Brief           : Toggle specific Pin
 *Parameters[in]  : GPIOx -> where x can be (A -> E)
 *Parameters[in]  : PIN_No-> specifies the pin to be toggled
 *Return Value    : None
 *Note            : None
 *=====================================================================
 */
void MCAL_GPIO_TogglePin(GPIO_TypeDef * GPIOx  , uint16_t PIN_No)
{
	GPIOx->ODR ^= PIN_No;
}


/**=====================================================================
 *Function        : MCAL_GPIO_LockPin
 *Brief           : The locking mechanism allows the IO config to be frozen
 *Parameters[in]  : GPIOx -> where x can be (A -> E)
 *Parameters[in]  : PIN_No-> specifies the pin to be locked
 *Return Value    : OK if Pin Config is locked or ERROR if pin is not locked
  	  	  	  	  	 @ref GPIO_Lock_Status
 *Note            : None
 *=====================================================================
 */
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef * GPIOx  , uint16_t PIN_No)
{
	volatile uint32_t tmp = 1<< 16 ;
	tmp |= PIN_No;
	GPIOx->LCKR = tmp;
	GPIOx->LCKR = PIN_No;
	GPIOx->LCKR = tmp;
	tmp = GPIOx->LCKR ;
	if((uint32_t)(GPIOx->LCKR & 1 << 16))
	{
		return GPIO_RETURN_LCK_EN  ;

	}
	else
	{
		return GPIO_RETURN_LCK_ERROR ;

	}
	return 0;

}
