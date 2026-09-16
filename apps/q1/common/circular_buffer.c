#include "circular_buffer.h"
#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

// Init the buffer
void cb_init(CircularBuffer *cb) {
    cb->lock = lock_create();
    if (cb->lock == SYNC_FAIL) {
        // Printf("Failed to create lock for circular buffer\n");
        // Exit();
    }
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

// Check if the buffer is full
int cb_is_full(CircularBuffer *cb) {
    return cb->count == BUFFER_CAPACITY;
}

// Check if the buffer is empty
int cb_is_empty(CircularBuffer *cb) {
    return cb->count == 0;
}

int cb_push(CircularBuffer *cb, char item) {
    if (cb_is_full(cb)) {
        return 0; // Buffer is full
    }
    cb->buffer[cb->head] = item;
    cb->head = (cb->head + 1) % BUFFER_CAPACITY;
    cb->count++;
    return 1; // Success
}

int cb_pop(CircularBuffer *cb, char *item) {
    if (cb_is_empty(cb)) {
        return 0; // Buffer is empty
    }
    *item = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % BUFFER_CAPACITY;
    cb->count--;
    return 1; // Success
}

int cb_peek(CircularBuffer *cb, char *item) {
    if (cb_is_empty(cb)) {
        return 0;
    }
    *item = cb->buffer[cb->tail];
    return 1;
}
