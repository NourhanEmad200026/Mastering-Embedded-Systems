/*
 * FIFO.c
 *
 *  Created on: Mar 28, 2024
 *      Author: nemad
 */
#include "FIFO.h"
#include "stdio.h"
#include "stdint.h"
E_FIFO_status FIFO_Enqueue(FIFO_Buf_t* FIFO, element_type item)
{
	if(!FIFO->base || !FIFO->head || !FIFO->tail)
		return FIFO_NULL;
	if(FIFO_IS_FULL(FIFO)== FIFO_Full)
		return FIFO_Full;

	*(FIFO->head) = item;
	FIFO->count ++;

	if(FIFO->head == (FIFO->base +(FIFO->length *sizeof(element_type))))
		FIFO->head = FIFO->base;

	FIFO->head++;
	return FIFO_no_error;
}

E_FIFO_status FIFO_Dequeue(FIFO_Buf_t* FIFO, element_type* item)
{
	if(!FIFO->base || !FIFO->head || !FIFO->tail)
		return FIFO_NULL;
	if(FIFO->count == 0)
	{
		printf("\nFIFO is empty.");
		return FIFO_empty;
	}

	*(item) = *(FIFO->tail);
	FIFO->count --;

	if(FIFO->tail == (FIFO->base + (FIFO->length * sizeof(element_type))))
		FIFO->tail = FIFO->base;

	FIFO->tail ++;
	return FIFO_no_error;

}

E_FIFO_status FIFO_IS_FULL (FIFO_Buf_t* FIFO)
{
	if(FIFO->count ==FIFO->length)
		return FIFO_Full;
	return FIFO_no_error;
}

E_FIFO_status FIFO_init (FIFO_Buf_t* FIFO, element_type* buff , unsigned int length)
{
	if(buff == NULL)
		return FIFO_NULL;
	FIFO->base = buff;
	FIFO->head = buff;
	FIFO->tail = buff;
	FIFO->length = length;
	FIFO->count =0;

	return FIFO_no_error;
}

void FIFO_Print(FIFO_Buf_t* FIFO)
{
	element_type* temp;
	int i;
	if(FIFO->count == 0)
		printf("\nFIFO is empty.\n");
	else{
		temp = FIFO->tail;
		printf("==============FIFO Print============");
		for(i = 0; i < FIFO->count; i++)
		{
			printf("\n                %X \n", *temp);
			temp ++;
		}
		printf("====================================");
	}
}
