#ifndef _RINGBUF_H /* Stop recursively including this header */
#define _RINGBUF_H

#include "stm32l4xx_hal.h"
#include <string.h>
#define RING_BUFFER_SIZE 256

typedef struct RingBuf {
  volatile uint8_t buffer[RING_BUFFER_SIZE];
  volatile uint8_t start, end;
} RingBuf;

void ringbuf_init(RingBuf*);
int8_t ringbuf_add(RingBuf*, uint8_t);
int8_t ringbuf_peek(RingBuf*, uint8_t*);
int8_t ringbuf_empty(RingBuf*);

#endif /* _RINGBUF_H */
