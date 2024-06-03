/*
 * main.c
 *
 *  Created on: May 25, 2024
 *      Author: nemad
 */
#include <avr/io.h>
#include <util/delay.h>

static unsigned char Seven_Segment[] = {
    // Segments for digits 0 to 9
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};
int main(){
	DDRA = 0xFF;
	while(1)
	{
		for(int i =0 ; i < 10 ;i ++)
		{
			PORTA = Seven_Segment[i];
			_delay_ms(500);
		}
	}
}
