/*
 * main.c
 *
 *  Created on: May 25, 2024
 *      Author: nemad
 */
#include <avr/interrupt.h>
#include <util/delay.h>
//#include "memory_map.h"
#include "utils.h"
#include <avr/io.h>

//set clock 8MHz
#define F_CPU 8000000UL



int main(void)
{
	DDRA = 0xFF;
	PORTA = 0xFF;
//	ClrBit(DDRC,0);
//	SetBit(PORTC,0);

	while(1)
	{
		for(int i = 0; i < 8 ;i++)
		{
			SetBit(PORTA,i);
			_delay_ms(1000);
		}
		for(int i = 7; i >= 0 ;i--)
		{
			ClrBit(PORTA,i);
			_delay_ms(1000);
		}
	}
}
