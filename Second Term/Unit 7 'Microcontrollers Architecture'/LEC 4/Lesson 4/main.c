/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "STM32F103x6.h"
#include "GPIO.h"
#include "EXTI.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "7_Segment.h"
unsigned int IRQ_FLag = 0;

//void EXTI9PB9_CALLBACK(void)
//{
//	IRQ_FLag = 1;
//	LCD_WRITE_STRING("IRQ EXTIL9 occured");
//	for(int i = 0; i <10000;i++);
//}
void wait_ms(uint32_t time){
	uint32_t i , j;
	for(i =0; i < time; i++)
		for(j = 0; j< 255 ;j++ );
}


void GPIO_INIT(){
	GPIO_PIN_CFG_t PinCFG;

	PinCFG.GPIO_PIN_Number = GPIO_PIN_1;
	PinCFG.GPIO_mode = GPIO_Mode_Input_Floating;
	MCAL_GPIO_Init(GPIOA, &PinCFG);

	PinCFG.GPIO_PIN_Number = GPIO_PIN_1;
	PinCFG.GPIO_mode = GPIO_Mode_Output_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCFG);


	PinCFG.GPIO_PIN_Number = GPIO_PIN_13;
	PinCFG.GPIO_mode = GPIO_Mode_Input_Floating;
	MCAL_GPIO_Init(GPIOA, &PinCFG);

	PinCFG.GPIO_PIN_Number = GPIO_PIN_13;
	PinCFG.GPIO_mode = GPIO_Mode_Output_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCFG);

}

void CLK_Init(){
	RCC_GPIOA_CLKEN() ;
	RCC_GPIOB_CLKEN() ;
}
int main(void)
{
	CLK_Init();
	GPIO_INIT();

	while(1)
	{
		if(MCAL_GPIO_ReadPIN(GPIOA, GPIO_PIN_1) == 0)
		{
			MCAL_GPIO_TogglePIN(GPIOB, GPIO_PIN_1);
			while(MCAL_GPIO_ReadPIN(GPIOA, GPIO_PIN_1) == 0);
		}
		if(MCAL_GPIO_ReadPIN(GPIOA, GPIO_PIN_13) == 1)
		{
			MCAL_GPIO_TogglePIN(GPIOB, GPIO_PIN_13);
			//while(MCAL_GPIO_ReadPIN(GPIOB, GPIO_PIN_1) == 0);
		}

		wait_ms(1);
	}

}



////enable clock
//	RCC_GPIOA_CLKEN();
//	RCC_GPIOB_CLKEN();
//	AFIO_GPIOE_CLKEN();
//
//	LCD_INIT();
//	LCD_clear_screen();
//
//	EXTI_PIN_CFG_t EXTI_CFG ;
//	EXTI_CFG.EXTI_PIN = EXTI9PB9 ;
//	EXTI_CFG.Trigger_Case = EXTI_Trigger_Rising;
//	EXTI_CFG.P_IRQ_CallBack = EXTI9PB9_CALLBACK;
//	EXTI_CFG.IRQ_Enable = EXTI_IRQ_Enable ;
//
//	MCAL_EXTI_GPIO_Init(&EXTI_CFG);
//	IRQ_FLag = 1;
//	while (1)
//	{
//		if(IRQ_FLag){
//			LCD_clear_screen();
//			IRQ_FLag =0;
//		}
//	}
//
//	/* Loop forever */
//	for(;;);