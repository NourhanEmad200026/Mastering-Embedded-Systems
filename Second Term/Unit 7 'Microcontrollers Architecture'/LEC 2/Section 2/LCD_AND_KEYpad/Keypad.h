/*
 * Keypad.h
 *
 *  Created on: May 28, 2024
 *      Author: nemad
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/io.h>

#define F_CPU 8000000UL

#define KEYPAD_PORT PORTD
#define KEYPAD_DIR  DDRD
#define KEYPAD_PIN PIND

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define C0 4
#define C1 5
#define C2 6
#define C3 7

void KeyPad_Init();
char Get_Char();


#endif /* KEYPAD_H_ */
