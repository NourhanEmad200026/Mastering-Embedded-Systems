/*
 * pressure_sensor.c
 *
 *  Created on: May 2, 2024
 *      Author: nemad
 */

#include "pressure_sensor.h"
#include "driver.h"

 void (* pressure_sensor_state)();

volatile static int pVAL;

STATE_define(init)
{
	pressure_sensor_state = ST_define(Preading);
}
STATE_define(Preading)
{
	pressure_sensor_state_ID = pressure_sensor_reading ;

	pVAL = getPressureVal();

	SET_Pressure_VAL(pVAL);

	pressure_sensor_state = ST_define(Pwaiting);

}
STATE_define(Pwaiting)
{
	pressure_sensor_state_ID = pressure_sensor_waiting ;

	Delay(10000);

	pressure_sensor_state = ST_define(Preading);
}


