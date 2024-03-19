/*
 * ass1q2.c
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */
#include <stdio.h>
#define area_circle(r) 3.14*r*r
int main()
{
	float r;
	printf("Enter radius of circle: ");
	fflush(stdout); fflush(stdin);
	scanf("%f",&r);
	fflush(stdout); fflush(stdin);
	printf("\nArea of circle = %f",area_circle(r));
}
