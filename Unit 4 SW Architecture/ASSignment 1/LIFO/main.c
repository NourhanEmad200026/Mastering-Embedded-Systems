/*
 * main.c
 *
 *  Created on: Mar 27, 2024
 *      Author: nemad
 */
#include "LIFO.h"
#include "stdlib.h"
#include "stdint.h"
#include "stdio.h"

Buf_type buf_l[blength];

void main()
{
    unsigned int temp = 0;

    LIFO_BUF_t Buf_1, Buf_2;

    LIFO_init(&Buf_1, buf_l, blength);

    for (int i = 0; i < 5; i++)
    {
        if (LIFO_Push_item(&Buf_1, i) == LIFO_no_error)
            printf("LIFO item add: %d\n", i);
    }

    for (int i = 0; i < 5; i++)
    {
        if (LIFO_Pop_item(&Buf_1, &temp) == LIFO_no_error)
            printf("LIFO get item: %d\n", temp);
    }
}
