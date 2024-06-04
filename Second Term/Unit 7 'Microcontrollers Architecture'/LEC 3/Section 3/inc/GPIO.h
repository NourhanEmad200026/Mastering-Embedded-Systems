/*
 * GPIO.h
 *
 *  Created on: May 28, 2024
 *      Author: nemad
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

//Includes
#include "STM32F103x6.h"

//==================================================================
//Configuration Structure
//==================================================================
typedef struct{
	uint16_t GPIO_PIN_Number  ;   //Specifies the GPIO Pins to be configured
                                  // This parameter can be a value of @ref GPIO pins
	uint8_t GPIO_mode         ;   //Specifies the operating mode for the selected pins
    							  // This parameter can be a value of @ref GPIO modes
	uint8_t GPIO_Output_Speed ;   //Specifies the speed for the selected pins
								  //This parameter can be a value of @ref GPIO Speed
}GPIO_PIN_CFG_t;














//==================================================================
//Macros Configuration References
//==================================================================

//@ref GPIO Pins

#define GPIO_PIN_0                 ((uint16_t)0x0001)  // 001
#define GPIO_PIN_1                 ((uint16_t)0x0002)  // 010
#define GPIO_PIN_2                 ((uint16_t)0x0004)  // 100
#define GPIO_PIN_3                 ((uint16_t)0x0008)  // 1000
#define GPIO_PIN_4                 ((uint16_t)0x0010)
#define GPIO_PIN_5                 ((uint16_t)0x0020)
#define GPIO_PIN_6                 ((uint16_t)0x0040)
#define GPIO_PIN_7                 ((uint16_t)0x0080)
#define GPIO_PIN_8                 ((uint16_t)0x0100)
#define GPIO_PIN_9                 ((uint16_t)0x0200)
#define GPIO_PIN_10                ((uint16_t)0x0400)
#define GPIO_PIN_11                ((uint16_t)0x0800)
#define GPIO_PIN_12                ((uint16_t)0x1000)
#define GPIO_PIN_13                ((uint16_t)0x2000)
#define GPIO_PIN_14                ((uint16_t)0x4000)
#define GPIO_PIN_15                ((uint16_t)0x8000)
#define GPIO_PIN_ALL               ((uint16_t)0xFFFF)

#define GPIO_Pin_Mask              0x0000FFFFu          // pin mask for assert test

//@ref GPIO modes
#define GPIO_Mode_Analog           0x00000000u
#define GPIO_Mode_Input_Floating   0x00000001u
#define GPIO_Mode_Input_PU         0x00000002u
#define GPIO_Mode_Input_PD         0x00000003u
#define GPIO_Mode_Output_PP        0x00000004u
#define GPIO_Mode_Output_OD        0x00000005u
#define GPIO_Mode_Output_AF_PP     0x00000006u
#define GPIO_Mode_Output_AF_OD     0x00000007u
#define GPIO_Mode_AF_Input         0x00000008u

//@ref GPIO speeds
#define GPIO_SPEED_10M             0x00000001u
#define GPIO_SPEED_2M              0x00000002u
#define GPIO_SPEED_50M             0x00000003u

//@ref GPIO_PIN_state
#define GPIO_PIN_SET               1
#define GPIO_PIN_RESET             0

//@ref GPIO_Lock
#define GPIO_LOCK_EN               1
#define GPIO_LOCK_ERROR            0

/*
 *==================================================================
 *                        APIs supported by "MCAL GPIO DRIVER"
 *==================================================================
*/

void MCAL_GPIO_Init (GPIO_TypeDef * GPIOx , GPIO_PIN_CFG_t * PIN_CFG) ;
void MCAL_GPIO_DeInit (GPIO_TypeDef * GPIOx);
uint8_t MCAL_GPIO_ReadPIN (GPIO_TypeDef * GPIOx , uint16_t PIN_Number);
uint16_t MCAL_GPIO_ReadPort (GPIO_TypeDef * GPIOx);
void MCAL_GPIO_WritePIN (GPIO_TypeDef * GPIOx , uint16_t PIN_Number, uint8_t value);
void MCAL_GPIO_WritePort (GPIO_TypeDef * GPIOx , uint16_t value);
void MCAL_GPIO_TogglePIN (GPIO_TypeDef * GPIOx , uint16_t PIN_Number);
uint8_t MCAL_GPIO_LockPIN (GPIO_TypeDef * GPIOx , uint16_t PIN_Number);












#endif /* INC_GPIO_H_ */














