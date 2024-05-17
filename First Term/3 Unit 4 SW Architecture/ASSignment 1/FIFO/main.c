/*
 * main.c
 *
 *  Created on: Mar 28, 2024
 *      Author: nemad
 */


#include "FIFO.h"
#define Buffer_length 5
element_type Buffer_1[Buffer_length];
void main()
{
	FIFO_Buf_t uart_fifo;
	unsigned int i;
	element_type temp =0 ;

	if(FIFO_init(&uart_fifo, Buffer_1, 5)== FIFO_no_error)
	{
		printf("FIFO Init ---------Done\n");
	}
	for(i=0;i<7;i++)
	{
		printf("\nFIFO Enqueue (%x) \n", i);
		if(FIFO_Enqueue(&uart_fifo, i)== FIFO_no_error)
			printf("\nFIFO Enqueue (%X) --- Done \n", i);
		else
			printf("\nFIFO Enqueue (%X) --- Failed \n", i);
	}


	if(FIFO_Dequeue(&uart_fifo ,&temp) == FIFO_no_error)
		printf("\t\nFIFO Dequeue %x------- Done \n",temp);

	if(FIFO_Dequeue( &uart_fifo ,&temp) == FIFO_no_error)
		printf("\t\nFIFO Dequeue %x------- Done \n",temp);
	FIFO_Print(&uart_fifo);
}
