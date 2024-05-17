/*
 * alarm_monitor.c
 *
 *  Created on: May 2, 2024
 *      Author: nemad
 */
#include "alarm_monitor.h"


void (* alarm_monitor_state)();

void high_pressure_detected(){
	alarm_monitor_state = ST_define(alarmON);
}

STATE_define(alarmOFF){
	alarm_monitor_state_ID = alarm_OFF ;
	Stop_Alarm();
}
STATE_define(alarmON){
	alarm_monitor_state_ID = alarm_ON ;
	Start_Alarm();
	alarm_monitor_state = ST_define(alarmWaiting);
}
STATE_define(alarmWaiting)
{
	alarm_monitor_state_ID = alarm_waiting;

	alarm_monitor_state = ST_define(alarmOFF);
}





