/*
 * GPIO.c
 *
 *  Created on: May 28, 2024
 *      Author: nemad
 */

/*===================INCLUDES===============================================================================*/
#include "GPIO.h"
/*==========================================================================================================*/

/*=========================================================================================================
 *                               GENERIC FUNCTIONS
 *==========================================================================================================
 */

uint8_t Get_CRLH_position(uint16_t PinNumber)
{
	switch(PinNumber)
	{
	case GPIO_PIN_0:
		return 0;
		break;
	case GPIO_PIN_1:
		return 4;
		break;
	case GPIO_PIN_2:
		return 8;
		break;
	case GPIO_PIN_3:
		return 12;
		break;
	case GPIO_PIN_4:
		return 16;
		break;
	case GPIO_PIN_5:
		return 20;
		break;
	case GPIO_PIN_6:
		return 24;
		break;
	case GPIO_PIN_7:
		return 28;
		break;
	case GPIO_PIN_8:
		return 0;
		break;
	case GPIO_PIN_9:
		return 4;
		break;
	case GPIO_PIN_10:
		return 8;
		break;
	case GPIO_PIN_11:
		return 12;
		break;
	case GPIO_PIN_12:
		return 16;
		break;
	case GPIO_PIN_13:
		return 20;
		break;
	case GPIO_PIN_14:
		return 24;
		break;
	case GPIO_PIN_15:
		return 28;
		break;
	}
	return 0;
}



/*=========================================================================================================
 *                              APIs FUNCTIONS Definitions
 *==========================================================================================================
 */



/*==========================================================================================================
 *                       Function Description
 *---------------------------------------------------------------------------------------------------------
 *  Function            :MCAL_GPIO_Init
 *  Brief               :Initializes the GPIOX Pin Y according to the specified parameters in the PIN config
 *  Parameters [Input]  :GPIOx, where x can be(A,B,...E) to select the GPIO peripheral
 *  Parameters [Input]  :Pin Cfg pointer to a GPIO_pin cfg structure to select the pin
 *  Return Value        :None
 *  Note                :STM32F103C6 has A,B,C,D,E GPIO modules but
 *                       LQFP48 has only A,B Part of C,D and E not found
 *==========================================================================================================
 */
void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_PIN_CFG_t *PIN_CFG)
{
    //port config CRL for pins (0 -> 7)
    //port config CRH for pins (8 -> 15)
    volatile uint32_t *CFGREG = NULL;
    uint8_t PIN_Config = 0;
    CFGREG = (PIN_CFG->GPIO_PIN_Number < GPIO_PIN_8) ? &GPIOx->CRL : &GPIOx->CRH;

    //clear mode[1:0] and CNF[1:0]
    (*CFGREG) &= ~(0xF << Get_CRLH_position(PIN_CFG->GPIO_PIN_Number));

    // if pin is output
    if ((PIN_CFG->GPIO_mode == GPIO_Mode_Output_AF_OD) || (PIN_CFG->GPIO_mode == GPIO_Mode_Output_AF_PP) || (PIN_CFG->GPIO_mode == GPIO_Mode_Output_OD) || (PIN_CFG->GPIO_mode == GPIO_Mode_Output_PP))
    {
        //Set CNF[1:0] MODE[1:0]
        PIN_Config = ((((PIN_CFG->GPIO_mode - 4) << 2) | (PIN_CFG->GPIO_Output_Speed)) & 0x0F); // CNF and mode cfg
    }
    //if pin is input
    else //MODE = 00 : Input mode (reset state)
    {
        if ((PIN_CFG->GPIO_mode == GPIO_Mode_Input_Floating) || (PIN_CFG->GPIO_mode == GPIO_Mode_Analog))
        {
            //Set CNF [1:0] MODE:[1:0] 00
            PIN_Config = ((((PIN_CFG->GPIO_mode) << 2) | 0x0) & 0x0F); // CNF and mode cfg
        }
        else if ((PIN_CFG->GPIO_mode == GPIO_Mode_AF_Input)) //consider it ad input floating
        {
            PIN_Config = (((GPIO_Mode_Input_Floating) << 2) | 0x0) & 0x0F; // CNF and mode cfg
        }
        else //PU PD Input
        {
            PIN_Config = (((GPIO_Mode_Input_PU) << 2) | 0x0) & 0x0F; // CNF and mode cfg

            if (PIN_CFG->GPIO_mode == GPIO_Mode_Input_PU)
            {
                //Table 20 port bit config, ODR = 1 in Input Pull UP
                GPIOx->ODR |= PIN_CFG->GPIO_PIN_Number;
            }
            else
            {
                //Table 20 port bit config, ODR = 0 in Input Pull Down
                GPIOx->ODR &= ~PIN_CFG->GPIO_PIN_Number;
            }
        }
    }

    // write on CRL or CRH
    (*CFGREG) |= ((PIN_Config) << Get_CRLH_position(PIN_CFG->GPIO_PIN_Number));
}

/*==========================================================================================================
 *                       Function Description
 *---------------------------------------------------------------------------------------------------------
 *  Function            :MCAL_GPIO_DeInit
 *  Brief               :Initializes the GPIOX Pin Y according to the specified parameters in the PIN config
 *  Parameters [Input]  :GPIOx, where x can be(A,B,...E) to select the GPIO peripheral
 *  Return Value        :None
 *  Note                :None
 *==========================================================================================================
 */
void MCAL_GPIO_DeInit (GPIO_TypeDef * GPIOx)
{
	//RCC_APB2 Reset Register
	if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR |= (1 << 2);
		RCC->APB2RSTR &=~ (1 << 2);
	}
	if(GPIOx == GPIOB)
	{
		RCC->APB2RSTR |= (1 << 3);
		RCC->APB2RSTR &=~ (1 << 3);
	}
	if(GPIOx == GPIOC)
	{
		RCC->APB2RSTR |= (1 << 4);
		RCC->APB2RSTR &=~ (1 << 4);
	}
	if(GPIOx == GPIOD)
	{
		RCC->APB2RSTR |= (1 << 5);
		RCC->APB2RSTR &=~ (1 << 5);
	}
	if(GPIOx == GPIOE)
	{
		RCC->APB2RSTR |= (1 << 6);
		RCC->APB2RSTR &=~ (1 << 6);
	}

}
/*==========================================================================================================
 *                       Function Description
 *---------------------------------------------------------------------------------------------------------
 *  Function            :MCAL_GPIO_ReadPIN
 *  Brief               :Read specific pin
 *  Parameters [Input]  :GPIOx, where x can be(A,B,...E) to select the GPIO peripheral
 *  Parameters [Input]  :Pin number: Set pin number according to @ref GPIO PINS
 *  Return Value        :the input pin value @ref GPIO_PIN_state
 *  Note                :None
 *==========================================================================================================
 */
uint8_t MCAL_GPIO_ReadPIN (GPIO_TypeDef * GPIOx , uint16_t PIN_Number)
{
	uint8_t bit_status;
	if(((GPIOx->IDR) & PIN_Number) != (uint32_t)GPIO_PIN_RESET)
	{
		bit_status = GPIO_PIN_SET;
	}
	else{
		bit_status = GPIO_PIN_RESET;
	}
	return bit_status;
}

/*==========================================================================================================
 *                       Function Description
 *---------------------------------------------------------------------------------------------------------
 *  Function            :MCAL_GPIO_ReadPort
 *  Brief               :Read specific pin
 *  Parameters [Input]  :GPIOx, where x can be(A,B,...E) to select the GPIO peripheral
 *  Return Value        :the input port value
 *  Note                :None
 *==========================================================================================================
 */
uint16_t MCAL_GPIO_ReadPort (GPIO_TypeDef * GPIOx)
{
	uint16_t PORTval ;
	PORTval = (uint16_t)GPIOx->IDR;
	return PORTval;
}

/*==========================================================================================================
 *                       Function Description
 *---------------------------------------------------------------------------------------------------------
 *  Function            :MCAL_GPIO_WritePIN
 *  Brief               :Write on specific pin
 *  Parameters [Input]  :GPIOx, where x can be(A,B,...E) to select the GPIO peripheral
 *  Parameters [Input]  :Pin number: Set pin number according to @ref GPIO PINS
 *  Parameters [Input]  :Pin value
 *  Return Value        :None
 *  Note                :None
 *==========================================================================================================
 */
void MCAL_GPIO_WritePIN (GPIO_TypeDef * GPIOx , uint16_t PIN_Number, uint8_t value)
{
	if(value  !=  GPIO_PIN_RESET)
	{
		//GPIOx->ODR |= PIN_Number;
		GPIOx->BSRR = (uint32_t)PIN_Number;
	}
	else{
		GPIOx->BRR =(uint32_t)PIN_Number;
	}
}
/*==========================================================================================================
 *                       Function Description
 *---------------------------------------------------------------------------------------------------------
 *  Function            :MCAL_GPIO_WritePort
 *  Brief               :Write on specific port
 *  Parameters [Input]  :GPIOx, where x can be(A,B,...E) to select the GPIO peripheral
 *  Parameters [Input]  :Port value
 *  Return Value        :None
 *  Note                :None
 *==========================================================================================================
 */
void MCAL_GPIO_WritePort (GPIO_TypeDef * GPIOx , uint16_t value)
{
	GPIOx->ODR = (uint32_t)value;
}
/*==========================================================================================================
 *                       Function Description
 *---------------------------------------------------------------------------------------------------------
 *  Function            :MCAL_GPIO_TogglePIN
 *  Brief               :Toggles the specified GPIO PIN
 *  Parameters [Input]  :GPIOx, where x can be(A,B,...E) to select the GPIO peripheral
 *  Parameters [Input]  :Pin number: Set pin number to read
 *  Return Value        :None
 *  Note                :None
 *==========================================================================================================
 */
void MCAL_GPIO_TogglePIN (GPIO_TypeDef * GPIOx , uint16_t PIN_Number)
{
	GPIOx->ODR ^= (PIN_Number);
}
/*==========================================================================================================
 *                       Function Description
 *---------------------------------------------------------------------------------------------------------
 *  Function            :MCAL_GPIO_LockPIN
 *  Brief               :The locking mechanism allows the IO cfg to be frozen
 *  Parameters [Input]  :GPIOx, where x can be(A,B,...E) to select the GPIO peripheral
 *  Parameters [Input]  :Pin number: Set pin number to read
 *  Return Value        :OK if pin cfg is locked or ERROR if pin not Locked(@ref GPIO_Lock)
 *  Note                :None
 *==========================================================================================================
 */
uint8_t MCAL_GPIO_LockPIN (GPIO_TypeDef * GPIOx , uint16_t PIN_Number)
{
	//set lock 16
	volatile uint32_t temp = 1 << 16 ;
	//set the LCKy
	temp |= PIN_Number;

	// write 1
	GPIOx->LCKR = temp;
	//write 0
	GPIOx->LCKR = PIN_Number;
	// write 1
	GPIOx->LCKR = temp;
	// read 0
	temp = GPIOx->LCKR;
	// read 1
	if((uint32_t) (GPIOx->LCKR & 1 << 16))
	{
		return GPIO_LOCK_EN;
	}
	else
	{
		return GPIO_LOCK_ERROR;
	}
}
