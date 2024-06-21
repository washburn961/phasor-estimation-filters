#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#define _USE_MATH_DEFINES

#include "phasor_filters_conf.h"
#include <complex.h>
#include <math.h>
#include <stdint.h>

typedef struct
{
    float content[BUFFER_SIZE];
    uint32_t head;
    uint32_t tail;
    uint32_t isFull;
    uint32_t size;
} SlidingBuffer;

void SlidingBuffer_Init(SlidingBuffer* buffer);
void SlidingBuffer_Write(SlidingBuffer* buffer, float data);
float SlidingBuffer_Read(SlidingBuffer* buffer, uint32_t index);
void SlidingBuffer_GetSamples(SlidingBuffer* buffer, float* out, uint32_t outSize);

#endif