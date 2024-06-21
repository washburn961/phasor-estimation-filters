#include "ring_buffer.h"

void SlidingBuffer_Init(SlidingBuffer* buffer)
{
    buffer->head = 0;
    buffer->tail = 0;
    buffer->isFull = 0;

    for (int i = 0; i < BUFFER_SIZE; ++i) {
        buffer->content[i] = 0;
    }
}

void SlidingBuffer_Write(SlidingBuffer* buffer, float data)
{
    buffer->content[buffer->tail] = data;
    buffer->head = (buffer->head + 1) % BUFFER_SIZE;
    buffer->tail = (buffer->tail + 1) % BUFFER_SIZE;
    buffer->isFull = buffer->tail == buffer->head;
}

// float SlidingBuffer_Read(SlidingBuffer* buffer, uint32_t index)
// {
//     uint32_t actualIndex = (buffer->head + index) % BUFFER_SIZE;
//     return buffer->content[actualIndex];
// }

float SlidingBuffer_Read(SlidingBuffer* buffer, uint32_t index) {
    // Calculate actual index relative to tail, moving backwards
    uint32_t actualIndex;
    if (index <= buffer->tail) {
        actualIndex = buffer->tail - index - 1;
    }
    else {
        actualIndex = BUFFER_SIZE + buffer->tail - index - 1;
    }

    return buffer->content[actualIndex % BUFFER_SIZE];
}


// void SlidingBuffer_GetSamples(SlidingBuffer* buffer, float* out, uint32_t outSize)
// {
//     for (uint32_t i = BUFFER_SIZE - outSize; i < BUFFER_SIZE; i++)
//     {
//         out[i] = SlidingBuffer_Read(buffer, i);
//     }
// }

void SlidingBuffer_GetSamples(SlidingBuffer* buffer, float* out, uint32_t outSize) {
    if (outSize > BUFFER_SIZE) outSize = BUFFER_SIZE; // Limit to buffer size

    for (uint32_t i = 0; i < outSize; ++i) {
        // Use the updated SlidingBuffer_Read to fetch samples in reverse order
        out[i] = SlidingBuffer_Read(buffer, outSize - i - 1);
    }
}
