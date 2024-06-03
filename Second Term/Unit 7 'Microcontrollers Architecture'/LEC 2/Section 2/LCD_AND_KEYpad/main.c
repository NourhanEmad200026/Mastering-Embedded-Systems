/*
 * main.c
 *
 *  Created on: May 26, 2024
 *      Author: nemad
 */

#include"LCD.h"
#include "Keypad.h"

int main(void)
{
	LCD_INIT();
	KeyPad_Init();
	char pressed_key ;

	//LCD_WRITE_STRING("Welcome Nourhan");
	while(1)
	{
		pressed_key = Get_Char();
		switch(pressed_key)
		{
		case ('!'):
				LCD_clear_screen();
				break;
		case ('N'):
				break;
		default :
			LCD_WRITE_CHAR(pressed_key);
			break;
		}
	}

}
