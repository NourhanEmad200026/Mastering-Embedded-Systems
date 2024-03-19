/*
 * main.c
 *
 *  Created on: Jan 3, 2024
 *      Author: nemad
 */
#include <stdio.h>
#include <stdlib.h>
struct SEmployee{
	char *name;
	int ID;
};
int main(){
	struct SEmployee emp1={"Nourhan",24},emp2={"Ali",19},emp3={"Youssef",19},emp4={"Alex",1002};
	struct SEmployee (*arr[])={&emp1,&emp2,&emp3,&emp4};
	struct SEmployee (*(*p)[4])=arr;
	printf("Employee name : %s\n",(*(*p+3))->name);
	printf("Employee name : %d\n",(*(*p+3))->ID);
}

