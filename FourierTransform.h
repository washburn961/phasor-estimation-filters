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

#ifndef FOURIER_TRANSFORM
#define FOURIER_TRANSFORM

#ifndef DFT_SIZE
#define DFT_SIZE 16
#endif

#define _USE_MATH_DEFINES

#include <stdint.h>
#include <math.h>

typedef struct
{
    float real[DFT_SIZE];
    float imag[DFT_SIZE];
    float sin[DFT_SIZE * DFT_SIZE];
    float cos[DFT_SIZE * DFT_SIZE];
} FourierTransform;

void FourierTransform_Init(FourierTransform* fourierTransform);
void FourierTransform_Evaluate(FourierTransform* fourierTransform, float* input, uint32_t inputSize);
float FourierTransform_GetMag(FourierTransform* fourierTransform, uint32_t index);
float FourierTransform_GetPhase(FourierTransform* fourierTransform, uint32_t index);
void FourierTransform_GetMagBin(FourierTransform* fourierTransform, float* out_magBin);

#endif