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
 * This library provides an implementation of the Fourier Transform for signal analysis,
 * specifically designed to work with a sliding window buffer for continuous signal input.
 * It allows for the efficient computation of the real and imaginary components, magnitude,
 * and phase of the signal's harmonics. This is particularly useful in digital signal processing
 * applications, where analyzing the frequency components of a signal is crucial. The library
 * integrates with a sliding buffer mechanism, facilitating the analysis of streaming data by
 * maintaining a dynamic, cyclical buffer of the most recent samples for transformation.
 */

#ifndef HALF_CYCLE_FOURIER_TRANSFORM
#define HALF_CYCLE_FOURIER_TRANSFORM

#ifndef HCDFT_SIZE
#define HCDFT_SIZE 16
#endif

#define _USE_MATH_DEFINES

#include <stdint.h>
#include <math.h>

typedef struct
{
    float real[HCDFT_SIZE];
    float imag[HCDFT_SIZE];
    float sin[(HCDFT_SIZE) * (HCDFT_SIZE / 2)];
    float cos[(HCDFT_SIZE) * (HCDFT_SIZE / 2)];
} HalfCycleFourierTransform;

void HalfCycleFourierTransform_Init(HalfCycleFourierTransform* fourierTransform);
void HalfCycleFourierTransform_Evaluate(HalfCycleFourierTransform* fourierTransform, float* input, uint32_t inputSize);
float HalfCycleFourierTransform_GetMag(HalfCycleFourierTransform* fourierTransform, uint32_t index);
float HalfCycleFourierTransform_GetPhase(HalfCycleFourierTransform* fourierTransform, uint32_t index);
void HalfCycleFourierTransform_GetMagBin(HalfCycleFourierTransform* fourierTransform, float* out_magBin);

#endif