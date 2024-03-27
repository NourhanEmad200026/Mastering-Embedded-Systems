/*
 * LIFO.c
 *
 *  Created on: Mar 27, 2024
 *      Author: nemad
 */

#include "LIFO.h"
#include "stdio.h"

LIFO_status LIFO_Push_item(LIFO_BUF_t *buf, Buf_type item)
{
    if (!buf || !buf->base || !buf->head)
        return LIFO_null;
    if (LIFO_is_full(buf) == LIFO_Full)
        return LIFO_Full;

    *(buf->head) = item;
    buf->head++;
    buf->count++;

    return LIFO_no_error;
}

LIFO_status LIFO_Pop_item(LIFO_BUF_t *buf, Buf_type *item)
{
    if (!buf || !buf->base || !buf->head)
        return LIFO_null;
    if (buf->base == buf->head)
        return LIFO_empty;

    buf->head--;
    *(item) = *(buf->head);
    buf->count--;

    return LIFO_no_error;
}

LIFO_status LIFO_init(LIFO_BUF_t *buf, unsigned int *Buf, unsigned int Buf_length)
{
    if (Buf == NULL)
        return LIFO_null;
    buf->base = Buf;
    buf->head = Buf;
    buf->length = Buf_length;
    buf->count = 0;
    return LIFO_no_error;
}

LIFO_status LIFO_is_full(LIFO_BUF_t *buf)
{
    if (!buf || !buf->base || !buf->head)
        return LIFO_null;

    if (buf->head >= (buf->base + buf->length))
        return LIFO_Full;

    return LIFO_no_error;
}
