#include <FourierTransform.h>

void FourierTransform_Init(FourierTransform* fourierTransform)
{
    for (int i = 0; i < FILTER_SIZE; i++)
    {
        fourierTransform->real[i] = 0;
        fourierTransform->imag[i] = 0;
    }
    SlidingBuffer_Init(&fourierTransform->input_buffer);
}
void FourierTransform_Evaluate(FourierTransform* fourierTransform, float newSample)
{
    SlidingBuffer_Write(&fourierTransform->input_buffer, newSample);

    for (int h = 0; h < FILTER_SIZE; h++)
    {
        float real = 0;
        float imag = 0;

        for (int n = 0; n < FILTER_SIZE; n++)
        {
            real += SlidingBuffer_Read(&fourierTransform->input_buffer, n) * cosf((2 * M_PI * h * n) / FILTER_SIZE);
            imag += SlidingBuffer_Read(&fourierTransform->input_buffer, n) * sinf((2 * M_PI * h * n) / FILTER_SIZE);
        }

        fourierTransform->real[h] = 2 * real / FILTER_SIZE;
        fourierTransform->imag[h] = -2 * imag / FILTER_SIZE;
    }
}

float FourierTransform_GetReal(FourierTransform* fourierTransform, uint32_t harmonicIndex)
{
    return fourierTransform->real[harmonicIndex];
}

float FourierTransform_GetImag(FourierTransform* fourierTransform, uint32_t harmonicIndex)
{
    return fourierTransform->imag[harmonicIndex];
}

float FourierTransform_GetMagnitude(FourierTransform* fourierTransform, uint32_t harmonicIndex)
{
    return sqrtf(
        powf(FourierTransform_GetReal(fourierTransform, harmonicIndex), 2) 
        + powf(FourierTransform_GetImag(fourierTransform, harmonicIndex), 2)
        );
}

float FourierTransform_GetPhase(FourierTransform* fourierTransform, uint32_t harmonicIndex)
{
    return atanf(FourierTransform_GetImag(fourierTransform, harmonicIndex) / FourierTransform_GetReal(fourierTransform, harmonicIndex));
}