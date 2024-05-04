/*
 * FIFO.h
 *
 *  Created on: Mar 28, 2024
 *      Author: nemad
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "stdio.h"
#include "stdint.h"


#define element_type uint8_t

typedef struct{
	unsigned int length;
	unsigned int count;
	element_type* base;
	element_type* head;
	element_type* tail;
}FIFO_Buf_t;

typedef enum{
	FIFO_NULL,
	FIFO_no_error,
	FIFO_empty,
	FIFO_Full,
}E_FIFO_status;


E_FIFO_status FIFO_Enqueue(FIFO_Buf_t* FIFO, element_type item);

E_FIFO_status FIFO_Dequeue(FIFO_Buf_t* FIFO, element_type* item);

E_FIFO_status FIFO_IS_FULL (FIFO_Buf_t* FIFO);

E_FIFO_status FIFO_init (FIFO_Buf_t* FIFO, element_type* buff , unsigned int length);

void FIFO_Print(FIFO_Buf_t* FIFO);



#endif /* FIFO_H_ */
