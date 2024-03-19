#include <CosineFilter.h>

void CosineFilter_Init(CosineFilter* cosineFilter)
{
    for (int i = 0; i < FILTER_SIZE; i++)
    {
        cosineFilter->real[i] = 0;
        cosineFilter->imag[i] = 0;
    }
    SlidingBuffer_Init(&cosineFilter->input_buffer);
}
void CosineFilter_Evaluate(CosineFilter* cosineFilter, float newSample)
{
    SlidingBuffer_Write(&cosineFilter->input_buffer, newSample);

    for (int h = 0; h < FILTER_SIZE; h++)
    {
        float real = 0;
        float imag = 0;

        for (int n = 0; n < FILTER_SIZE; n++)
        {
            real += SlidingBuffer_Read(&cosineFilter->input_buffer, n) * cosf((2 * M_PI * h * n) / FILTER_SIZE);
            imag += SlidingBuffer_Read(&cosineFilter->input_buffer, (n + FILTER_SIZE / 4)) * cosf((2 * M_PI * h * n) / FILTER_SIZE);
        }

        cosineFilter->real[h] = 2 * real / FILTER_SIZE;
        cosineFilter->imag[h] = -2 * imag / FILTER_SIZE;
    }
}

float CosineFilter_GetReal(CosineFilter* cosineFilter, uint32_t harmonicIndex)
{
    return cosineFilter->real[harmonicIndex];
}

float CosineFilter_GetImag(CosineFilter* cosineFilter, uint32_t harmonicIndex)
{
    return cosineFilter->imag[harmonicIndex];
}

float CosineFilter_GetMagnitude(CosineFilter* cosineFilter, uint32_t harmonicIndex)
{
    return sqrtf(
        powf(CosineFilter_GetReal(cosineFilter, harmonicIndex), 2) 
        + powf(CosineFilter_GetImag(cosineFilter, harmonicIndex), 2)
        );
}

float CosineFilter_GetPhase(CosineFilter* cosineFilter, uint32_t harmonicIndex)
{
    return atanf(CosineFilter_GetImag(cosineFilter, harmonicIndex) / CosineFilter_GetReal(cosineFilter, harmonicIndex));
}