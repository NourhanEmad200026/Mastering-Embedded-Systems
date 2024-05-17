/*
 * alarm_monitor.h
 *
 *  Created on: May 2, 2024
 *      Author: nemad
 */

#ifndef ALARM_MONITOR_H_
#define ALARM_MONITOR_H_

#include "states.h"
#include "driver.h"
enum{
	alarm_OFF ,
	alarm_ON ,
	alarm_waiting
}alarm_monitor_state_ID;
STATE_define(alarmOFF);
STATE_define(alarmON);
STATE_define(alarmWaiting);

extern void (* alarm_monitor_state)();


#endif /* ALARM_MONITOR_H_ */
