/*
 * main_Algorithm.h
 *
 *  Created on: May 2, 2024
 *      Author: nemad
 */

#ifndef MAIN_ALGORITHM_H_
#define MAIN_ALGORITHM_H_

#include "states.h"

enum{
	High_pressure_detected
}high_pressure_ID;

extern void (*main_algorithm)() ;


STATE_define(high_Pressure_Detected);


#endif /* MAIN_ALGORITHM_H_ */
