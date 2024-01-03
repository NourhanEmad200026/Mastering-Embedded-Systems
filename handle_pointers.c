/*
 * main.c
 *
 *  Created on: Jan 3, 2024
 *      Author: nemad
 */
#include <stdio.h>
#include <stdlib.h>

int main(){
	int m =29;
	printf("m = %d, address of m =%p\n",m,&m);
	int *ab=&m;
	printf("ab= %d, address of ab =%p\n",*ab,ab);
	*ab=34;
	printf("ab = %d, address of ab =%p\n",*ab,ab);
	*ab=7;
	printf("m = %d, address of m =%p",m,&m);
}

