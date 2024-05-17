/*
 * ass1q2.c
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */
#include <stdio.h>
#include <string.h>
struct Sdistance{
	float inch;
	int feet;
}d1,d2,sum;
int main()
{
	printf("Enter information for 1st distance: ");
	printf("\nEnter feet: ");
	fflush(stdout);
	scanf("%d",&d1.feet);
	printf("\nEnter inch: ");
	fflush(stdout);
	scanf("%f",&d1.inch);
	printf("\nEnter information for 2nd distance: ");
	printf("\nEnter feet: ");
	fflush(stdout);
	scanf("%d",&d2.feet);
	printf("\nEnter inch: ");
	fflush(stdout);
	scanf("%f",&d2.inch);
	sum.feet=d1.feet+d2.feet;
	sum.inch=d1.inch+d2.inch;
	if(sum.inch>12.0)
	{
		sum.inch=sum.inch-12.0;
		++sum.feet;
	}
	printf("\nSum of distances = %d\'-%.1f\"",sum.feet,sum.inch);

}
