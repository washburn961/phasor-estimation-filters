#ifndef COSINE_FILTER
#define COSINE_FILTER


#ifndef COSINE_FILTER_SIZE
#define COSINE_FILTER_SIZE 16
#endif

#define COSINE_FILTER_BUFFER_SIZE (COSINE_FILTER_SIZE + COSINE_FILTER_SIZE / 4)

#define _USE_MATH_DEFINES

#include <stdint.h>
#include <math.h>

typedef struct
{
    float real[COSINE_FILTER_SIZE];
    float imag[COSINE_FILTER_SIZE];
    float cos[COSINE_FILTER_SIZE * COSINE_FILTER_SIZE];
} CosineFilter;

void CosineFilter_Init(CosineFilter* cosineFilter);
void CosineFilter_Evaluate(CosineFilter* cosineFilter, float* input, uint32_t inputSize);
float CosineFilter_GetMag(CosineFilter* cosineFilter, uint32_t index);
float CosineFilter_GetPhase(CosineFilter* cosineFilter, uint32_t index);

#endif