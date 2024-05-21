/*
 * main.c
 *
 *  Created on: May 21, 2024
 *      Author: nemad
 */
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>

ISR(INT0_vect)
{
	PORTD |= (1 << PD5);
	_delay_ms(100);
	PORTD &=~ (1 << PD5);
}
ISR(INT1_vect)
{
	PORTD |= (1 << PD6);
	_delay_ms(100);
	PORTD &=~ (1 << PD6);
}
ISR(INT2_vect)
{
	PORTD |= (1 << PD7);
	_delay_ms(100);
	PORTD &=~ (1 << PD7);
}
int main()
{
	// Enable: INT0 on PORT D pin 2, LED on PORT D pin 5
	DDRD |= (1 << PD5);
	DDRD &=~ (1 << PD2);
	GICR|= (1 << INT0);
	MCUCR |= (1 << ISC00);
	// Enable: INT1 on PORT D pin 3, LED on PORT D pin 6
	DDRD |= (1 << PD6);
	DDRD &=~ (1 << PD3);
	GICR|= (1 << INT1);
	MCUCR |= (11 << ISC10);
	// Enable: INT2 on PORT B pin 2, LED on PORT D pin 7
	DDRD |= (1 << PD7);
	DDRB &=~ (1 << PD2);
	GICR|= (1 << INT2);


	SREG |= (1 << 7); // enable global interrupts

	while(1);


}


