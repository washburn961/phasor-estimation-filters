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
 * The HalfCycleFourierTransform library offers a specialized approach to Fourier
 * transform analysis by focusing on half-cycle signal segments. This method is
 * particularly useful in applications requiring precise frequency resolution over
 * shorter time windows, such as in electrical engineering and signal processing.
 * It employs a sliding window buffer to continuously update and process signal
 * data, calculating real and imaginary parts, magnitude, and phase for each
 * harmonic component within the half-cycle window. This enables detailed
 * harmonic analysis in real-time applications, supporting dynamic signal
 * analysis with high temporal resolution.
 */


#ifndef HALF_CYCLE_FOURIER_TRANSFORM
#define HALF_CYCLE_FOURIER_TRANSFORM
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
} HalfCycleFourierTransform;

void HalfCycleFourierTransform_Init(HalfCycleFourierTransform* halfCycleFourierTransform);
void HalfCycleFourierTransform_Evaluate(HalfCycleFourierTransform* halfCycleFourierTransform, float newSample);
float HalfCycleFourierTransform_GetReal(HalfCycleFourierTransform* halfCycleFourierTransform, uint32_t harmonicIndex);
float HalfCycleFourierTransform_GetImag(HalfCycleFourierTransform* halfCycleFourierTransform, uint32_t harmonicIndex);
float HalfCycleFourierTransform_GetMagnitude(HalfCycleFourierTransform* halfCycleFourierTransform, uint32_t harmonicIndex);
float HalfCycleFourierTransform_GetPhase(HalfCycleFourierTransform* halfCycleFourierTransform, uint32_t harmonicIndex);