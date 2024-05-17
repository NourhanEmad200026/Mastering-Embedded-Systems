/*
 * main_Algorithm.c
 *
 *  Created on: May 2, 2024
 *      Author: nemad
 */

#include "main_Algorithm.h"
#include "driver.h"

static int threshold = 20;
unsigned int pVal = 0;
void (*main_algorithm)() ;

void SET_Pressure_VAL(int pVAL)
{
	pVal = pVAL;
	main_algorithm = ST_define(high_Pressure_Detected);

}
STATE_define(high_Pressure_Detected)
{

	high_pressure_ID = High_pressure_detected ;
	if(pVal > threshold)
	{
		high_pressure_detected();
		main_algorithm = SET_Pressure_VAL;
	}
	else
	{
		main_algorithm = SET_Pressure_VAL;
	}
}
