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
 * This library is designed to perform sine filtering on signal data, utilizing
 * a sliding window buffer for continuous input management. It is especially suited
 * for signal processing applications where sine wave analysis is critical. The library
 * computes the real and imaginary components, magnitude, and phase of the signal's
 * sine components, facilitating comprehensive signal analysis. Its implementation
 * supports dynamic data processing, making it ideal for real-time signal monitoring
 * and analysis tasks.
 */


#ifndef SINE_FILTER
#define SINE_FILTER
#endif

#ifndef FILTER_SIZE
#define FILTER_SIZE 16
#endif

#define _USE_MATH_DEFINES

#define BUFFER_SIZE (FILTER_SIZE + FILTER_SIZE / 4)

#include <SlidingBuffer.h>
#include <stdint.h>
#include <math.h>

typedef struct
{
    float real[FILTER_SIZE];
    float imag[FILTER_SIZE];
    SlidingBuffer input_buffer;
} SineFilter;

void SineFilter_Init(SineFilter* sineFilter);
void SineFilter_Evaluate(SineFilter* sineFilter, float newSample);
float SineFilter_GetReal(SineFilter* sineFilter, uint32_t harmonicIndex);
float SineFilter_GetImag(SineFilter* sineFilter, uint32_t harmonicIndex);
float SineFilter_GetMagnitude(SineFilter* sineFilter, uint32_t harmonicIndex);
float SineFilter_GetPhase(SineFilter* sineFilter, uint32_t harmonicIndex);