#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H
#include "lab2-api.h"
#define BUFFER_CAPACITY 10

typedef struct {
    lock_t lock;
    cond_t cond_full;
    cond_t cond_empty;
    lock_t lock_full;
    lock_t lock_empty;
    char buffer[BUFFER_CAPACITY];
    int head;
    int tail;
    int count;
} CircularBuffer;

void cb_init(CircularBuffer *cb);
int cb_is_full(CircularBuffer *cb);
int cb_is_empty(CircularBuffer *cb);
int cb_push(CircularBuffer *cb, char item);
int cb_pop(CircularBuffer *cb, char *item);
int cb_peek(CircularBuffer *cb, char *item);
#endif // CIRCULAR_BUFFER_H
