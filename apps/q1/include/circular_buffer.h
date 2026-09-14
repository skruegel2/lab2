#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#define BUFFER_CAPACITY 10

typedef struct {
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
#endif // CIRCULAR_BUFFER_H
