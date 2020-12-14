#include "ringbuf.h"

void ringbuf_init(RingBuf* buf) {
  if (buf == NULL) {
	return;
  }
  buf->start = buf->end = 0;
}

int8_t ringbuf_add(RingBuf* buf, uint8_t elem) {
  if (buf == NULL || buf->start == buf->end + 1) {
	return -1;
  }
  if (buf->end == RING_BUFFER_SIZE - 1 && buf->start == 0) {
	return -1;
  }
  buf->buffer[buf->end] = elem;
  buf->end++;
  
  if (buf->end == RING_BUFFER_SIZE) {
    buf->end = 0;
  }
  return 0;
}

int8_t ringbuf_peek(RingBuf* buf, uint8_t* result) {
  if (buf == NULL || buf->start == buf->end || result == NULL) {
	return -1;
  }

  *result = buf->buffer[buf->start];
  buf->start++;
  
  if (buf->start == RING_BUFFER_SIZE) {
	buf->start = 0;
  }
  return 0;
}

int8_t ringbuf_empty(RingBuf* buf) {
  if (buf == NULL) {
	return -1;
  }
  if (buf->start == buf->end) {
	return 1;
  }
  return 0;
}
