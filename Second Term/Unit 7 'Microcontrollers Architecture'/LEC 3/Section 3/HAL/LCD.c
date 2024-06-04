/*
 * lcd.c
 *
 * Created: 4/22/2021 3:01:11 PM
 *  Author: Nourhan
 */

#include "lcd.h"
GPIO_PIN_CFG_t PinCfg;



void LCD_clear_screen(){
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}

void LCD_lcd_kick(){
	//LCD_CTRL |= (1 << EN_SWITCH);
	MCAL_GPIO_WritePIN(LCD_CTRL, EN_SWITCH, GPIO_PIN_SET);

	wait_ms(50);
	//LCD_CTRL &= ~(1 << EN_SWITCH);
	MCAL_GPIO_WritePIN(LCD_CTRL, EN_SWITCH, GPIO_PIN_RESET);

}

void LCD_GOTO_XY(unsigned char line, unsigned char position){
	if (line == 1)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW+position);
		}
	}
	if (line == 2)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW+position);
		}
	}
}

void LCD_INIT(){
	wait_ms(20);
	//	DataDir_LCD_CTRL |= (1<<EN_SWITCH | 1<<RS_SWITCH | 1<<RW_SWITCH);
	//	LCD_CTRL &= ~ (1<<EN_SWITCH | 1<<RS_SWITCH | 1<<RW_SWITCH);
	//	DataDir_LCD_PORT = 0xFF;

	//Pins are set input floating
	PinCfg.GPIO_PIN_Number = EN_SWITCH ;
	PinCfg.GPIO_mode = GPIO_Mode_Input_Floating;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_Number = RS_SWITCH ;
	PinCfg.GPIO_mode = GPIO_Mode_Input_Floating;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_Number = RW_SWITCH ;
	PinCfg.GPIO_mode = GPIO_Mode_Input_Floating;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	wait_ms(15);

	// DAta pins output with speed 10 MHz
	PinCfg.GPIO_PIN_Number = GPIO_PIN_0 ;
	PinCfg.GPIO_mode = GPIO_Mode_Output_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_Number = GPIO_PIN_1 ;
	PinCfg.GPIO_mode = GPIO_Mode_Output_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_Number = GPIO_PIN_2 ;
	PinCfg.GPIO_mode = GPIO_Mode_Output_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_Number = GPIO_PIN_3 ;
	PinCfg.GPIO_mode = GPIO_Mode_Output_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_Number = GPIO_PIN_4 ;
	PinCfg.GPIO_mode = GPIO_Mode_Output_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_Number = GPIO_PIN_5 ;
	PinCfg.GPIO_mode = GPIO_Mode_Output_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_Number = GPIO_PIN_6 ;
	PinCfg.GPIO_mode = GPIO_Mode_Output_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_Number = GPIO_PIN_7 ;
	PinCfg.GPIO_mode = GPIO_Mode_Output_PP;
	PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);


	LCD_clear_screen();


#ifdef EIGHT_BIT_MODE
	LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
#endif
#ifdef FOUR_BIT_MODE
	//LCD_WRITE_COMMAND(0x02);		/* send for 4 bit initialization of LCD  */
	//LCD_WRITE_COMMAND(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
	//LCD_WRITE_COMMAND(0x0c);              /* Display on cursor off*/
	//LCD_WRITE_COMMAND(0x06);              /* Increment cursor (shift cursor to right)*/
	//LCD_WRITE_COMMAND(0x01);
	LCD_WRITE_COMMAND(0x02);
	LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
#endif
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
}

void LCD_check_lcd_isbusy(){
	//	DataDir_LCD_PORT &= ~(0xFF<<DATA_shift);
	//	LCD_CTRL |= (1 << RW_SWITCH);
	//	LCD_CTRL &= ~(1 << RS_SWITCH);
	//	LCD_lcd_kick();
	//	DataDir_LCD_PORT |= (0xFF<<DATA_shift);
	//	LCD_CTRL &= ~(1 << RW_SWITCH);
	PinCfg.GPIO_PIN_Number = GPIO_PIN_0 ;
	PinCfg.GPIO_mode = GPIO_Mode_Input_Floating;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_Number = GPIO_PIN_1 ;
	PinCfg.GPIO_mode = GPIO_Mode_Input_Floating;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_Number = GPIO_PIN_2 ;
	PinCfg.GPIO_mode = GPIO_Mode_Input_Floating;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_Number = GPIO_PIN_3 ;
	PinCfg.GPIO_mode = GPIO_Mode_Input_Floating;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_Number = GPIO_PIN_4 ;
	PinCfg.GPIO_mode = GPIO_Mode_Input_Floating;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_Number = GPIO_PIN_5 ;
	PinCfg.GPIO_mode = GPIO_Mode_Input_Floating;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_Number = GPIO_PIN_6 ;
	PinCfg.GPIO_mode = GPIO_Mode_Input_Floating;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_Number = GPIO_PIN_7 ;
	PinCfg.GPIO_mode = GPIO_Mode_Input_Floating;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	MCAL_GPIO_WritePIN(LCD_CTRL, RW_SWITCH, GPIO_PIN_SET);
	MCAL_GPIO_WritePIN(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);

	LCD_lcd_kick();

	MCAL_GPIO_WritePIN(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);

}


void LCD_WRITE_COMMAND(unsigned char command){
#ifdef EIGHT_BIT_MODE
	LCD_check_lcd_isbusy();
	MCAL_GPIO_WritePort(LCD_PORT, command);
//	LCD_CTRL &= ~((1 << RS_SWITCH) | (1<<RW_SWITCH));
	MCAL_GPIO_WritePIN(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePIN(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);

	wait_ms(1);
	LCD_lcd_kick();
#endif
#ifdef FOUR_BIT_MODE
	LCD_check_lcd_isbusy();
	LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
	LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
	LCD_lcd_kick ();
	LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
	LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
	LCD_lcd_kick();
#endif
}

void LCD_WRITE_CHAR(unsigned char character){
#ifdef EIGHT_BIT_MODE
	LCD_check_lcd_isbusy();
//	LCD_PORT = character;
//	LCD_CTRL &= ~(1 << RW_SWITCH);
//	LCD_CTRL |= (1 << RS_SWITCH);
	MCAL_GPIO_WritePort(LCD_PORT, character);
	MCAL_GPIO_WritePIN(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePIN(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET);

	wait_ms(1);
	LCD_lcd_kick();
#endif
#ifdef FOUR_BIT_MODE
	//LCD_check_lcd_isbusy();
	LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0);
	LCD_CTRL |= 1<<RS_SWITCH; //turn RS ON for Data mode.
	LCD_CTRL &= ~ (1<<RW_SWITCH);//turn RW off so you can write.
	LCD_lcd_kick();
	LCD_PORT = (LCD_PORT & 0x0F) | (character << 4);
	LCD_CTRL |= 1<<RS_SWITCH; //turn RS ON for Data mode.
	LCD_CTRL &= ~ (1<<RW_SWITCH);//turn RW off so you can write.
	LCD_lcd_kick ();
#endif
}

void LCD_WRITE_STRING(char* string){
	int count = 0;
	while (*string > 0){
		count++;
		LCD_WRITE_CHAR(*string++);
		if (count == 16)
		{
			LCD_GOTO_XY(2,0);
		}
		else if (count == 32)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(1,0);
			count = 0;
		}
	}
}
