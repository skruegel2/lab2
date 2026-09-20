#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H
#include "lab2-api.h"
#define BUFFER_CAPACITY 32

typedef struct {
    lock_t lock;
    char buffer[BUFFER_CAPACITY];
    int head;
    int tail;
    int count;
    cond_t not_full;  // Condition variable for buffer not full
    cond_t not_empty; // Condition variable for buffer not empty
} CircularBuffer;

void cb_init(CircularBuffer *cb);
int cb_is_full(CircularBuffer *cb);
int cb_is_empty(CircularBuffer *cb);
int cb_push(CircularBuffer *cb, char item);
int cb_pop(CircularBuffer *cb, char *item);
int cb_peek(CircularBuffer *cb, char *item);
#endif // CIRCULAR_BUFFER_H
