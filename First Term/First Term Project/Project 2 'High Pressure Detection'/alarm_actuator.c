/*
 * alarm_actuator.c
 *
 *  Created on: May 2, 2024
 *      Author: nemad
 */

#include "alarm_actuator.h"

void (* alarm_actuator_state)();

void Stop_Alarm(){
	Set_Alarm_actuator(1); // Stop the alarm
	alarm_actuator_state = ST_define(AAalarmOFF); // Transition to the alarm off state
}

void Start_Alarm()
{
	Set_Alarm_actuator(0); // Start the alarm
	alarm_actuator_state = ST_define(AAalarmON); // Transition to the alarm on state
}

STATE_define(AAinit){
	GPIO_INITIALIZATION();
	Stop_Alarm(); // Initialize by stopping the alarm
	alarm_actuator_state = ST_define(AAwaiting);
}

STATE_define(AAwaiting){
	alarm_actuator_state_ID = alarm_actuator_waiting;
}

STATE_define(AAalarmON){
	alarm_actuator_state_ID = alarm_actuator_alarmON; // Turn on the alarm

	// Add a delay for a certain time (in milliseconds) to keep the alarm on
	
	alarm_actuator_state = ST_define(AAalarmOFF); 
	
}

STATE_define(AAalarmOFF){
	alarm_actuator_state_ID = alarm_actuator_alarmOFF;
	Delay(6000);
	Stop_Alarm();
}
