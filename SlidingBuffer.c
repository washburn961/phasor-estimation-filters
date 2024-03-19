#include <SlidingBuffer.h>

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

    if (buffer->isFull)
    {
        buffer->head = (buffer->head + 1) % BUFFER_SIZE;
    }

    buffer->tail = (buffer->tail + 1) % BUFFER_SIZE;
    buffer->isFull = buffer->tail == buffer->head;
}

float SlidingBuffer_Read(SlidingBuffer* buffer, uint32_t index)
{
    uint32_t actualIndex = (buffer->head + index) % BUFFER_SIZE;
    return buffer->content[actualIndex];
}