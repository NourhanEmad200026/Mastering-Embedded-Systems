/*
 * states.h
 *
 *  Created on: May 2, 2024
 *      Author: nemad
 */

#ifndef STATES_H_
#define STATES_H_

#define STATE_define(_stateFUN_) void ST_##_stateFUN_()
#define ST_define(_stateFUN_) ST_##_stateFUN_

void Stop_Alarm();
void Start_Alarm();
void high_pressure_detected();
void SET_Pressure_VAL(int pVAL);

#endif /* STATES_H_ */
