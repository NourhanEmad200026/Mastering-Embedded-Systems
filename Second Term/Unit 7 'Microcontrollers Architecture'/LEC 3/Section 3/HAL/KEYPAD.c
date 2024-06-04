/*
 * Keypad.c
 *
 *  Created on: May 28, 2024
 *      Author: nemad
 */

#include "Keypad.h"

int KEYPAD_R[] ={R0 , R1 ,R2 , R3};
int KEYPAD_C[] ={C0 , C1 ,C2 , C3};

GPIO_PIN_CFG_t PinCFG  ;
void KeyPad_Init()
{
	//KEYPAD_DIR &=~ ((1 << R0) | (1 << R1) | (1 << R2) | (1 << R3));
	PinCFG.GPIO_PIN_Number =R0;
	PinCFG.GPIO_mode = GPIO_Mode_Output_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCFG);

	PinCFG.GPIO_PIN_Number =R1;
	PinCFG.GPIO_mode = GPIO_Mode_Output_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCFG);

	PinCFG.GPIO_PIN_Number =R2;
	PinCFG.GPIO_mode = GPIO_Mode_Output_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCFG);

	PinCFG.GPIO_PIN_Number =R3;
	PinCFG.GPIO_mode = GPIO_Mode_Output_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCFG);

	PinCFG.GPIO_PIN_Number =C0;
	PinCFG.GPIO_mode = GPIO_Mode_Output_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCFG);

	PinCFG.GPIO_PIN_Number =C1;
	PinCFG.GPIO_mode = GPIO_Mode_Output_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCFG);

	PinCFG.GPIO_PIN_Number =C2;
	PinCFG.GPIO_mode = GPIO_Mode_Output_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCFG);

	PinCFG.GPIO_PIN_Number =C3;
	PinCFG.GPIO_mode = GPIO_Mode_Output_PP;
	PinCFG.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCFG);



	MCAL_GPIO_WritePort(KEYPAD_PORT, 0xFF);
	//KEYPAD_DIR |=  ((1 << C0) | (1 << C1) | (1 << C2) | (1 << C3));
	//KEYPAD_PORT = 0xFF;

}
char Get_Char()
{
	int i , j;
	for(i = 0; i < 4 ; i++)
	{
		//KEYPAD_PORT |= ((1 << KEYPAD_C[0]) | (1 << KEYPAD_C[1])|(1 << KEYPAD_C[2])|(1 << KEYPAD_C[3]) );
		MCAL_GPIO_WritePIN(KEYPAD_PORT, KEYPAD_C[0],GPIO_PIN_SET);
		MCAL_GPIO_WritePIN(KEYPAD_PORT, KEYPAD_C[1],GPIO_PIN_SET);
		MCAL_GPIO_WritePIN(KEYPAD_PORT, KEYPAD_C[2],GPIO_PIN_SET);
		MCAL_GPIO_WritePIN(KEYPAD_PORT, KEYPAD_C[3],GPIO_PIN_SET);

		MCAL_GPIO_WritePIN(KEYPAD_PORT, KEYPAD_C[i],GPIO_PIN_RESET);


		//KEYPAD_PORT &=~ (1 << KEYPAD_C[i]);

		for(j = 0; j < 4 ; j++)
		{

			if(MCAL_GPIO_ReadPIN(KEYPAD_PORT, KEYPAD_R[j]) == 0)
			{
				while(MCAL_GPIO_ReadPIN(KEYPAD_PORT, KEYPAD_R[j]) == 0);
				switch(i)
				{
				case 0:
				{
					if(j == 0) return '7';
					else if (j == 1) return '4';
					else if (j == 2) return '1';
					else if (j == 1) return '?';
					break;
				}
				case 1:
				{
					if(j == 0) return '8';
					else if (j == 1) return '5';
					else if (j == 2) return '2';
					else if (j == 3) return '0';
					break;
				}
				case 2:
				{
					if(j == 0) return '9';
					else if (j == 1) return '6';
					else if (j == 2) return '3';
					else if (j == 3) return '=';
					break;
				}
				case 3:
				{
					if(j == 0) return '/';
					else if (j == 1) return '*';
					else if (j == 2) return '-';
					else if (j == 3) return '+';
					break;
				}


				}
			}
		}
	}
	return 'N';
}

