/*
 * Student_Management_System.h
 *
 *  Created on: Apr 28, 2024
 *      Author: nemad
 */

#ifndef STUDENT_MANAGEMENT_SYSTEM_H_
#define STUDENT_MANAGEMENT_SYSTEM_H_

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define DPRINTF(...) {fflush(stdin);\
		fflush(stdout);\
		printf(__VA_ARGS__);\
		fflush(stdin);\
		fflush(stdout);}

typedef struct {
	char fname[50];
	char lname[50];
	int roll ;
	float GPA ;
	int cid [5];
}sInfo;

sInfo buf[55];

typedef struct {
	sInfo* tail;
	sInfo* head;
	sInfo* base;
	int count;
	int length;
}FIFO_Buf;

FIFO_Buf student_managment;


typedef enum{
	FIFO_empty ,
	FIFO_Full ,
	FIFO_no_error ,
	FIFO_Null ,
	FIFO_error ,
}FIFO_Buf_status;


FIFO_Buf_status FIFO_init(FIFO_Buf * fifo, sInfo* buf , unsigned int length);
FIFO_Buf_status FIFO_Add_Manually(FIFO_Buf* fifo);
int check_roll_number(FIFO_Buf* fifo, int roll);
FIFO_Buf_status Find_by_roll(FIFO_Buf* fifo);
FIFO_Buf_status Find_by_fname(FIFO_Buf* fifo);
FIFO_Buf_status total_number(FIFO_Buf* fifo);
FIFO_Buf_status view_student(FIFO_Buf* fifo);
FIFO_Buf_status delete_student(FIFO_Buf* fifo);
FIFO_Buf_status update_student(FIFO_Buf* fifo);
FIFO_Buf_status FIFo_add_from_file(FIFO_Buf* fifo);





#endif /* STUDENT_MANAGEMENT_SYSTEM_H_ */
