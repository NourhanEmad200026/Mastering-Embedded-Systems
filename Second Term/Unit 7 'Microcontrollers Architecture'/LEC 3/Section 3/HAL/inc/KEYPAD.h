/*
 * Keypad.h
 *
 *  Created on: May 28, 2024
 *      Author: nemad
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "GPIO.h"
#include "STM32F103x6.h"
//#define F_CPU 8000000UL

#define KEYPAD_PORT GPIOB
//#define KEYPAD_DIR  DDRD
//#define KEYPAD_PIN PIND

#define R0 GPIO_PIN_0
#define R1 GPIO_PIN_1
#define R2 GPIO_PIN_3
#define R3 GPIO_PIN_4
#define C0 GPIO_PIN_5
#define C1 GPIO_PIN_6
#define C2 GPIO_PIN_7
#define C3 GPIO_PIN_14

void KeyPad_Init();
char Get_Char();


#endif /* KEYPAD_H_ */
