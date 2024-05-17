/*
 * main.c
 *
 *  Created on: May 2, 2024
 *      Author: nemad
 */
#include <stdint.h>
#include <stdio.h>

#include "driver.h"
#include "alarm_actuator.h"
#include "alarm_monitor.h"
#include "pressure_sensor.h"
#include "main_Algorithm.h"
void setup()
{
	alarm_monitor_state= ST_define(alarmOFF);
	alarm_actuator_state= ST_define(AAinit);
	pressure_sensor_state= ST_define(init);
	main_algorithm= ST_define(high_Pressure_Detected);
}
int main (){
	GPIO_INITIALIZATION();
	setup();
	while (1)
	{

		//Implement your Design
		pressure_sensor_state();
		main_algorithm();
		alarm_monitor_state();
		alarm_actuator_state();
	
	}

}

