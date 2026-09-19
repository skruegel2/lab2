#ifndef PRODUCER_H
#define PRODUCER_H

#include "circular_buffer.h"

#define PRODUCER_TO_RUN "producer.dlx.obj"

void producer_main(CircularBuffer *cb);

#endif // PRODUCER_H      