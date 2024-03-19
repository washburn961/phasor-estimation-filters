/*
 * MIT License
 * 
 * Copyright (c) Gabriel Bortoletto Molz
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * This library implements a sliding window type buffer, designed for efficient
 * management of data in a circular manner. It allows for dynamic data insertion
 * and retrieval, maintaining a fixed size and automatically overwriting old data
 * as new data comes in. This makes it particularly useful for applications that
 * require a continuous, fixed-size stream of data, such as in signal processing,
 * real-time monitoring, or any scenario where the latest data points are of
 * interest and older data can be discarded.
 */

#include <stdint.h>
#include <math.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 20
#endif

#ifndef SLIDING_BUFFER
#define SLIDING_BUFFER

typedef struct
{
    float content[BUFFER_SIZE];
    uint32_t head;
    uint32_t tail;
    uint32_t isFull;
} SlidingBuffer;

void SlidingBuffer_Init(SlidingBuffer* buffer);
void SlidingBuffer_Write(SlidingBuffer* buffer, float data);
float SlidingBuffer_Read(SlidingBuffer* buffer, uint32_t index);

#endif