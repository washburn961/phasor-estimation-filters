#include <SineFilter.h>

void SineFilter_Init(SineFilter* sineFilter)
{
    for (int i = 0; i < FILTER_SIZE; i++)
    {
        sineFilter->real[i] = 0;
        sineFilter->imag[i] = 0;
    }
    SlidingBuffer_Init(&sineFilter->input_buffer);
}

void SineFilter_Evaluate(SineFilter* sineFilter, float newSample)
{
    SlidingBuffer_Write(&sineFilter->input_buffer, newSample);

    for (int h = 0; h < FILTER_SIZE; h++)
    {
        float real = 0;
        float imag = 0;

        for (int n = 0; n < FILTER_SIZE; n++)
        {
            real += SlidingBuffer_Read(&sineFilter->input_buffer, (n + FILTER_SIZE / 4)) * sinf((2 * M_PI * h * n) / FILTER_SIZE);
            imag += SlidingBuffer_Read(&sineFilter->input_buffer, n) * sinf((2 * M_PI * h * n) / FILTER_SIZE);
        }

        sineFilter->real[h] = -2 * real / FILTER_SIZE;
        sineFilter->imag[h] = -2 * imag / FILTER_SIZE;
    }
}

float SineFilter_GetReal(SineFilter* sineFilter, uint32_t harmonicIndex)
{
    return sineFilter->real[harmonicIndex];
}

float SineFilter_GetImag(SineFilter* sineFilter, uint32_t harmonicIndex)
{
    return sineFilter->imag[harmonicIndex];
}

float SineFilter_GetMagnitude(SineFilter* sineFilter, uint32_t harmonicIndex)
{
    return sqrtf(
        powf(SineFilter_GetReal(sineFilter, harmonicIndex), 2) 
        + powf(SineFilter_GetImag(sineFilter, harmonicIndex), 2)
        );
}

float SineFilter_GetPhase(SineFilter* sineFilter, uint32_t harmonicIndex)
{
    return atanf(SineFilter_GetImag(sineFilter, harmonicIndex) / SineFilter_GetReal(sineFilter, harmonicIndex));
}