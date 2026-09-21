#ifndef CONSUMER_H
#define CONSUMER_H

#include "circular_buffer.h"

#define CONSUMER_TO_RUN "consumer.dlx.obj"

void consumer_main(CircularBuffer *cb);

#endif // CONSUMER_H    