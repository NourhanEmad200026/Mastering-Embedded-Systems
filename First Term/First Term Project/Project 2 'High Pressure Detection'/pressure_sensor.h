/*
 * pressure_sensor.h
 *
 *  Created on: May 2, 2024
 *      Author: nemad
 */

#ifndef PRESSURE_SENSOR_H_
#define PRESSURE_SENSOR_H_

#include "states.h"

enum{
	pressure_sensor_reading ,
	pressure_sensor_waiting ,
}pressure_sensor_state_ID;

STATE_define(init);
STATE_define(Preading);
STATE_define(Pwaiting);
extern void (* pressure_sensor_state)();

#endif /* PRESSURE_SENSOR_H_ */
