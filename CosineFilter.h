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
 * This library implements a Cosine Filter for signal processing, utilizing a
 * sliding window buffer to manage continuous input data. It is designed for
 * applications requiring cosine transform operations on streaming data. The
 * filter calculates real and imaginary parts of the cosine transform, allowing
 * for further analysis of the signal's magnitude and phase. It is particularly
 * useful in scenarios where the cosine components of a signal are of interest,
 * such as in harmonic analysis or in the development of cosine-based modulation
 * schemes.
 */


#ifndef COSINE_FILTER
#define COSINE_FILTER
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
} CosineFilter;

void CosineFilter_Init(CosineFilter* cosineFilter);
void CosineFilter_Evaluate(CosineFilter* cosineFilter, float newSample);
float CosineFilter_GetReal(CosineFilter* cosineFilter, uint32_t harmonicIndex);
float CosineFilter_GetImag(CosineFilter* cosineFilter, uint32_t harmonicIndex);
float CosineFilter_GetMagnitude(CosineFilter* cosineFilter, uint32_t harmonicIndex);
float CosineFilter_GetPhase(CosineFilter* cosineFilter, uint32_t harmonicIndex);