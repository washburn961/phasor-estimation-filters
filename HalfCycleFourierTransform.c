#include <HalfCycleFourierTransform.h>

void HalfCycleFourierTransform_Init(HalfCycleFourierTransform* halfCycleFourierTransform)
{
    for (int i = 0; i < FILTER_SIZE; i++)
    {
        halfCycleFourierTransform->real[i] = 0;
        halfCycleFourierTransform->imag[i] = 0;
    }
    SlidingBuffer_Init(&halfCycleFourierTransform->input_buffer);
}
void HalfCycleFourierTransform_Evaluate(HalfCycleFourierTransform* halfCycleFourierTransform, float newSample)
{
    SlidingBuffer_Write(&halfCycleFourierTransform->input_buffer, newSample);

    for (int h = 0; h < FILTER_SIZE; h++)
    {
        float real = 0;
        float imag = 0;

        for (int n = FILTER_SIZE / 2; n < FILTER_SIZE; n++)
        {
            real += SlidingBuffer_Read(&halfCycleFourierTransform->input_buffer, n) * cosf((2 * M_PI * h * n) / FILTER_SIZE);
            imag += SlidingBuffer_Read(&halfCycleFourierTransform->input_buffer, n) * sinf((2 * M_PI * h * n) / FILTER_SIZE);
        }

        halfCycleFourierTransform->real[h] = 4 * real / FILTER_SIZE;
        halfCycleFourierTransform->imag[h] = -4 * imag / FILTER_SIZE;
    }
}

float HalfCycleFourierTransform_GetReal(HalfCycleFourierTransform* halfCycleFourierTransform, uint32_t harmonicIndex)
{
    return halfCycleFourierTransform->real[harmonicIndex];
}

float HalfCycleFourierTransform_GetImag(HalfCycleFourierTransform* halfCycleFourierTransform, uint32_t harmonicIndex)
{
    return halfCycleFourierTransform->imag[harmonicIndex];
}

float HalfCycleFourierTransform_GetMagnitude(HalfCycleFourierTransform* halfCycleFourierTransform, uint32_t harmonicIndex)
{
    return sqrtf(
        powf(HalfCycleFourierTransform_GetReal(halfCycleFourierTransform, harmonicIndex), 2) 
        + powf(HalfCycleFourierTransform_GetImag(halfCycleFourierTransform, harmonicIndex), 2)
        );
}

float HalfCycleFourierTransform_GetPhase(HalfCycleFourierTransform* halfCycleFourierTransform, uint32_t harmonicIndex)
{
    return atanf(HalfCycleFourierTransform_GetImag(halfCycleFourierTransform, harmonicIndex) / HalfCycleFourierTransform_GetReal(halfCycleFourierTransform, harmonicIndex));
}