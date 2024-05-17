/*
 * alarm_actuator.h
 *
 *  Created on: May 2, 2024
 *      Author: nemad
 */

#ifndef ALARM_ACTUATOR_H_
#define ALARM_ACTUATOR_H_

#include "states.h"
#include "driver.h"
enum{
	alarm_actuator_waiting ,
	alarm_actuator_alarmON ,
	alarm_actuator_alarmOFF
}alarm_actuator_state_ID;

STATE_define(AAinit);
STATE_define(AAwaiting);
STATE_define(AAalarmON);
STATE_define(AAalarmOFF);
extern void (* alarm_actuator_state)();

#endif /* ALARM_ACTUATOR_H_ */
