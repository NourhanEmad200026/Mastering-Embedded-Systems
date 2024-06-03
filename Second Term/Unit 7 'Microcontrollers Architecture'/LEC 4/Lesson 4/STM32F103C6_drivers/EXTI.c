/*
 * GPIO.c
 *
 *  Created on: May 28, 2024
 *      Author: nemad
 */

/*===================INCLUDES===============================================================================*/
#include "EXTI.h"
#include "GPIO.h"
/*==========================================================================================================*/

/*=========================================================================================================
 *                               GENERIC VARIABLES
 *==========================================================================================================
 */

void (*GP_IRQ_CallBack[15])(void) ;




/*=========================================================================================================
 *                               GENERIC MACROS
 *==========================================================================================================
 */

#define AFIO_GPIO_EXTI_Mapping(x)   (   (x==GPIOA)?0 : \
		                                (x==GPIOB)?1 : \
		                                (x==GPIOC)?2 : \
		                                (x==GPIOD)?3 : 0   )


/*=========================================================================================================
 *                               GENERIC FUNCTIONS
 *==========================================================================================================
 */

void Enable_NVIC(uint16_t IRQ)
{
	switch (IRQ){
	case 0 :
		NVIC_IRQ6_EXTI0_Enable ;
		break;
	case 1 :
		NVIC_IRQ7_EXTI1_Enable ;
		break;
	case 2 :
		NVIC_IRQ8_EXTI2_Enable ;
		break;
	case 3 :
		NVIC_IRQ9_EXTI3_Enable ;
		break;
	case 4 :
		NVIC_IRQ10_EXTI4_Enable ;
		break;
	case 5 :
	case 6 :
	case 7 :
	case 8 :
	case 9 :
		NVIC_IRQ23_EXTI5_9_Enable ;
		break;
	case 10 :
	case 11 :
	case 12 :
	case 13 :
	case 14 :
	case 15 :
		NVIC_IRQ40_EXTI10_15_Enable ;
		break;
	}
}
void Disable_NVIC(uint16_t IRQ)
{
	switch (IRQ){
		case 0 :
			NVIC_IRQ6_EXTI0_Disable ;
			break;
		case 1 :
			NVIC_IRQ7_EXTI1_Disable ;
			break;
		case 2 :
			NVIC_IRQ8_EXTI2_Disable ;
			break;
		case 3 :
			NVIC_IRQ9_EXTI3_Disable ;
			break;
		case 4 :
			NVIC_IRQ10_EXTI4_Disable ;
			break;
		case 5 :
		case 6 :
		case 7 :
		case 8 :
		case 9 :
			NVIC_IRQ23_EXTI5_9_Disable ;
			break;
		case 10 :
		case 11 :
		case 12 :
		case 13 :
		case 14 :
		case 15 :
			NVIC_IRQ40_EXTI10_15_Disable ;
			break;
		}
}













void Update_EXTI(EXTI_PIN_CFG_t* EXTI_CFG)
{
	//1 Configure GPIO to be AF Input -> Floating Input
	GPIO_PIN_CFG_t PinCFG  ;
	PinCFG.GPIO_PIN_Number = EXTI_CFG->EXTI_PIN.GPIO_PIN  ;
	PinCFG.GPIO_mode = GPIO_Mode_Input_Floating           ;
	MCAL_GPIO_Init(EXTI_CFG->EXTI_PIN.GPIO_PORT, &PinCFG)  ;
	//==================================================

	//2 Update AFIO to route between EXTI line with Port A,B,C or D
	uint8_t AFIO_EXTICR_index = EXTI_CFG->EXTI_PIN.EXTI_Input_Line_Number / 4         ;

	uint8_t AFIO_EXTICR_positon = (EXTI_CFG->EXTI_PIN.EXTI_Input_Line_Number % 4 ) * 4;

	AFIO->EXTICR[AFIO_EXTICR_index] &=~ (0xF << AFIO_EXTICR_positon);

	AFIO->EXTICR[AFIO_EXTICR_index] |=(( AFIO_GPIO_EXTI_Mapping(EXTI_CFG->EXTI_PIN.GPIO_PORT) & 0x0F) << AFIO_EXTICR_positon);
	//==================================================

	//3 UPdate rising and falling edge
	EXTI->RTSR &=~ (1 << EXTI_CFG->EXTI_PIN.EXTI_Input_Line_Number);
	EXTI->FTSR &=~ (1 << EXTI_CFG->EXTI_PIN.EXTI_Input_Line_Number);

	if(EXTI_CFG->Trigger_Case == EXTI_Trigger_Rising)
	{
		EXTI->RTSR |= EXTI_CFG->EXTI_PIN.EXTI_Input_Line_Number;

	}else if(EXTI_CFG->Trigger_Case == EXTI_Trigger_Falling)
	{
		EXTI->FTSR |= EXTI_CFG->EXTI_PIN.EXTI_Input_Line_Number ;

	}else if(EXTI_CFG->Trigger_Case == EXTI_Trigger_RF)
	{
		EXTI->RTSR |= EXTI_CFG->EXTI_PIN.EXTI_Input_Line_Number;

		EXTI->FTSR |= EXTI_CFG->EXTI_PIN.EXTI_Input_Line_Number ;

	}
	//==================================================

	//4 UPdate IRQ Handling CALLBACK
	GP_IRQ_CallBack[EXTI_CFG->EXTI_PIN.EXTI_Input_Line_Number] = EXTI_CFG->P_IRQ_CallBack ;

	//==================================================

	//5 ENable /DISable IRQ Mask EXTI &&& NVIC

	if(EXTI_CFG->IRQ_Enable == EXTI_IRQ_Enable)
	{
		EXTI->IMR |=  (1 << EXTI_CFG->EXTI_PIN.EXTI_Input_Line_Number);
		Enable_NVIC(EXTI_CFG->EXTI_PIN.EXTI_Input_Line_Number);
	}else
	{
		EXTI->IMR &=~ (1 << EXTI_CFG->EXTI_PIN.EXTI_Input_Line_Number);
		Disable_NVIC(EXTI_CFG->EXTI_PIN.EXTI_Input_Line_Number);

	}
	//==================================================

}


/*=========================================================================================================
 *                              APIs FUNCTIONS Definitions
 *==========================================================================================================
 */


/*==========================================================================================================
 *                       Function Description
 *---------------------------------------------------------------------------------------------------------
 *  Function            :MCAL_EXTI_GPIO_Init
 *  Brief               :This is used to initialize the EXTI from specific GPIO PIN and specify the mask/Trigger condition & IRQ CallBack
 *  Parameters [Input]  :EXTI config set @ref EXTI_define , EXTI_Trigger_define & EXTI_IRQ_define
 *  Return Value        :None
 *  Note                :STM32F103C6 has A,B,C,D,E GPIO modules but
 *                       LQFP48 has only A,B Part of C,D and E not found
 *                      -Also MANDATORY to enable the clock of AFIO and corresponding GPIO
 *==========================================================================================================
 */
void MCAL_EXTI_GPIO_Init(EXTI_PIN_CFG_t * EXTI_CFG)
{
	Update_EXTI(EXTI_CFG);
}


/*==========================================================================================================
 *                       Function Description
 *---------------------------------------------------------------------------------------------------------
 *  Function            :MCAL_EXTI_GPIO_UPdate
 *  Brief               :This is used to update the EXTI from specific GPIO PIN and specify the mask/Trigger condition & IRQ CallBack
 *  Parameters [Input]  :EXTI config set @ref EXTI_define , EXTI_Trigger_define & EXTI_IRQ_define
 *  Return Value        :None
 *  Note                :STM32F103C6 has A,B,C,D,E GPIO modules but
 *                       LQFP48 has only A,B Part of C,D and E not found
 *                      -Also MANDATORY to enable the clock of AFIO and corresponding GPIO
 *==========================================================================================================
 */
void MCAL_EXTI_GPIO_UPdate(EXTI_PIN_CFG_t * EXTI_CFG)
{
	Update_EXTI(EXTI_CFG);
}

/*==========================================================================================================
 *                       Function Description
 *---------------------------------------------------------------------------------------------------------
 *  Function            :MCAL_EXTI_GPIO_DeInit
 *  Brief               :reset EXTI Registers and NVIC corresponding to IRQ mask
 *  Return Value        :None
 *  Note                :None
 *==========================================================================================================
 */
void MCAL_EXTI_GPIO_DeInit(void)
{
	EXTI->IMR   = 0x00000000 ;
	EXTI->EMR   = 0x00000000 ;
	EXTI->RTSR  = 0x00000000 ;
	EXTI->FTSR  = 0x00000000 ;
	EXTI->SWIER = 0x00000000 ;
	EXTI->PR    = 0xFFFFFFFF ;   //write 1 to clear

	//Disable EXTI IRQ From NVIC
	NVIC_IRQ6_EXTI0_Disable       ;
	NVIC_IRQ7_EXTI1_Disable       ;
	NVIC_IRQ8_EXTI2_Disable       ;
	NVIC_IRQ9_EXTI3_Disable       ;
	NVIC_IRQ10_EXTI4_Disable      ;
	NVIC_IRQ23_EXTI5_9_Disable    ;
	NVIC_IRQ40_EXTI10_15_Disable  ;
}




/*==========================================================================================================
                                ISR FUNCTIONS
 *==========================================================================================================
 */

void EXTI0_IRQHandler(void)
{
	//clear Interrupt by w 1 to clear into Pending Resgister (EXTI_PR)
	EXTI->PR |= 1 << 0    ;
	// call IRQ
	GP_IRQ_CallBack[0]()  ;
}
void EXTI1_IRQHandler(void)
{
	//clear Interrupt by w 1 to clear into Pending Resgister (EXTI_PR)
	EXTI->PR |= 1 << 1    ;
	// call IRQ
	GP_IRQ_CallBack[1]()  ;
}
void EXTI2_IRQHandler(void)
{
	//clear Interrupt by w 1 to clear into Pending Resgister (EXTI_PR)
	EXTI->PR |= 1 << 2    ;
	// call IRQ
	GP_IRQ_CallBack[2]()  ;
}
void EXTI3_IRQHandler(void)
{
	//clear Interrupt by w 1 to clear into Pending Resgister (EXTI_PR)
	EXTI->PR |= 1 << 3    ;
	// call IRQ
	GP_IRQ_CallBack[3]()  ;

}
void EXTI4_IRQHandler(void)
{
	//clear Interrupt by w 1 to clear into Pending Resgister (EXTI_PR)
	EXTI->PR |= 1 << 4    ;
	// call IRQ
	GP_IRQ_CallBack[4]()  ;
}
void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & 1 << 5) { EXTI->PR |= (1 << 5)     ; GP_IRQ_CallBack[5]()   ; }
	if(EXTI->PR & 1 << 6) { EXTI->PR |= (1 << 6)     ; GP_IRQ_CallBack[6]()   ; }
	if(EXTI->PR & 1 << 7) { EXTI->PR |= (1 << 7)     ; GP_IRQ_CallBack[7]()   ; }
	if(EXTI->PR & 1 << 8) { EXTI->PR |= (1 << 8)     ; GP_IRQ_CallBack[8]()   ; }
	if(EXTI->PR & 1 << 9) { EXTI->PR |= (1 << 9)     ; GP_IRQ_CallBack[9]()   ; }
}
void EXTI15_10_IRQHandler (void)
{
	if(EXTI->PR & 1 << 10) { EXTI->PR |= (1 << 10)     ; GP_IRQ_CallBack[10]()   ; }
	if(EXTI->PR & 1 << 11) { EXTI->PR |= (1 << 11)     ; GP_IRQ_CallBack[11]()   ; }
	if(EXTI->PR & 1 << 12) { EXTI->PR |= (1 << 12)     ; GP_IRQ_CallBack[12]()   ; }
	if(EXTI->PR & 1 << 13) { EXTI->PR |= (1 << 13)     ; GP_IRQ_CallBack[13]()   ; }
	if(EXTI->PR & 1 << 14) { EXTI->PR |= (1 << 14)     ; GP_IRQ_CallBack[14]()   ; }
	if(EXTI->PR & 1 << 15) { EXTI->PR |= (1 << 15)     ; GP_IRQ_CallBack[15]()   ; }

}



