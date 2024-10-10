/*
 * GPIO.h
 *
 *  Created on: Aug 3, 2024
 *      Author: nemad
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

//=============================================================
//=========================INCLUDES============================
//=============================================================

#include "stm32F103C6.h"

//=============================================================
//=====================CONFIG STRUCTURE========================
//=============================================================

typedef struct
{
	uint16_t GPIO_PinNumber  ; //Specifies the GPIO pin number to be configured
	                          //This parameter can be a value of @ref GPIO_PINS_define

	uint8_t GPIO_MODE        ; //Specifies the mode of the selected pin
    						  //This parameter can be a value of @ref GPIO_MODE_define

	uint8_t GPIO_Output_Speed ;//Specifies the speed of the selected output pin
							   //This parameter can be a value of @ref GPIO_Speed_define


}GPIO_PinCFG_T;



//=============================================================
//================MACROS CONFIG REFERENCE======================
//=============================================================

//--------------@ref GPIO_PINS_define--------------------------
#define GPIO_PIN_0                           ((uint16_t)0x0001)
#define GPIO_PIN_1                           ((uint16_t)0x0002)  // = 0010 = 1 << 1
#define GPIO_PIN_2                           ((uint16_t)0x0004)  // = 0100 = 1 << 2
#define GPIO_PIN_3                           ((uint16_t)0x0008)
#define GPIO_PIN_4                           ((uint16_t)0x0010)
#define GPIO_PIN_5                           ((uint16_t)0x0020)
#define GPIO_PIN_6                           ((uint16_t)0x0040)
#define GPIO_PIN_7                           ((uint16_t)0x0080)
#define GPIO_PIN_8                           ((uint16_t)0x0100)
#define GPIO_PIN_9                           ((uint16_t)0x0200)
#define GPIO_PIN_10                          ((uint16_t)0x0400)
#define GPIO_PIN_11                          ((uint16_t)0x0800)
#define GPIO_PIN_12                          ((uint16_t)0x1000)
#define GPIO_PIN_13                          ((uint16_t)0x2000)
#define GPIO_PIN_14                          ((uint16_t)0x4000)
#define GPIO_PIN_15                          ((uint16_t)0x8000)
#define GPIO_PIN_ALL                         ((uint16_t)0xFFFF)
#define GPIO_PIN_MASK                        0x0000FFFFu


//--------------@ref GPIO_MODE_define--------------------------
#define GPIO_MODE_Analog                            0x00000000u
#define GPIO_MODE_Input_Flo                         0x00000001u
#define GPIO_MODE_Input_PU                          0x00000002u
#define GPIO_MODE_Input_PD                          0x00000003u
#define GPIO_MODE_Output_PP                         0x00000004u
#define GPIO_MODE_Output_OD                         0x00000005u
#define GPIO_MODE_Output_AF_PP                      0x00000006u
#define GPIO_MODE_Output_AF_OD                      0x00000007u
#define GPIO_MODE_AF_Input                          0x00000008u

//--------------@ref GPIO_Speed_define--------------------------
#define GPIO_SPEED_10M                              0x00000001u
#define GPIO_SPEED_2M                               0x00000002u
#define GPIO_SPEED_50M                              0x00000003u

//----------------@ref GPIO_Pin_State--------------------------
#define PIN_RESET                                             0
#define PIN_SET                                               1

//----------------@ref GPIO_Lock_Status-------------------------
#define GPIO_RETURN_LCK_EN                                    1
#define GPIO_RETURN_LCK_ERROR                                 0




//=============================================================
//===========APIs Supported by MCAL GPIO Driver================
//=============================================================

void MCAL_GPIO_Init(GPIO_TypeDef * GPIOx , GPIO_PinCFG_T * PIN_CFG);
void MCAL_GPIO_DeInit(GPIO_TypeDef * GPIOx);


uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef * GPIOx  , uint16_t PIN_No);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef * GPIOx );

void MCAL_GPIO_WritePin(GPIO_TypeDef * GPIOx  , uint16_t PIN_No , uint8_t value);
void MCAL_GPIO_WritePort(GPIO_TypeDef * GPIOx  ,  uint16_t value);

void MCAL_GPIO_TogglePin(GPIO_TypeDef * GPIOx  , uint16_t PIN_No);

uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef * GPIOx  , uint16_t PIN_No);


#endif /* INC_GPIO_H_ */
