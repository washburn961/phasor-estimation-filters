#ifndef FOURIER_TRANSFORM_H
#define FOURIER_TRANSFORM_H

#define _USE_MATH_DEFINES

#include "phasor_filters_conf.h"
#include <complex.h>
#include <math.h>
#include <stdint.h>

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