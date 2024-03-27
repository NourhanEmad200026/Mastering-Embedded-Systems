/*
 * LIFO.h
 *
 *  Created on: Mar 27, 2024
 *      Author: nemad
 */

#ifndef LIFO_H_
#define LIFO_H_

#include "stdint.h"
#include "stdio.h"

#define Buf_type uint8_t

#define blength 5

extern Buf_type buf_l[blength];

typedef struct
{
    unsigned int length;
    unsigned int count;
    unsigned int *base;
    unsigned int *head;
} LIFO_BUF_t;

typedef enum
{
    LIFO_Full,
    LIFO_no_error,
    LIFO_empty,
    LIFO_null,
} LIFO_status;

LIFO_status LIFO_Push_item(LIFO_BUF_t *buf, Buf_type item);
LIFO_status LIFO_Pop_item(LIFO_BUF_t *buf, Buf_type *item);
LIFO_status LIFO_init(LIFO_BUF_t *buf, unsigned int *Buf, unsigned int Buf_length);
LIFO_status LIFO_is_full(LIFO_BUF_t *buf);

#endif /* LIFO_H_ */
