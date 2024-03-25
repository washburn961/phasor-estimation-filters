#include "FourierTransform.h"

void FourierTransform_Init(FourierTransform* fourierTransform)
{
    for (int i = 0; i < DFT_SIZE; i++)
    {
        fourierTransform->real[i] = 0;
        fourierTransform->imag[i] = 0;
    }

    for (int h = 0; h < DFT_SIZE; h++)
    {
        for (int n = 0; n < DFT_SIZE; n++)
        {
            fourierTransform->sin[h * DFT_SIZE + n] = sinf((2 * M_PI * h * n) / DFT_SIZE);
            fourierTransform->cos[h * DFT_SIZE + n] = cosf((2 * M_PI * h * n) / DFT_SIZE);
        }
    }
}
void FourierTransform_Evaluate(FourierTransform* fourierTransform, float* input, uint32_t inputSize)
{
    if (inputSize > DFT_SIZE)
    {
        inputSize = DFT_SIZE;
    }

    for (int h = 0; h < DFT_SIZE; h++)
    {
        float real = 0;
        float imag = 0;

        for (int n = 0; n < DFT_SIZE; n++)
        {
            real += input[n] * fourierTransform->cos[h * DFT_SIZE + n];
            imag += input[n] * fourierTransform->sin[h * DFT_SIZE + n];
        }

        fourierTransform->real[h] = 2 * real / DFT_SIZE;
        fourierTransform->imag[h] = -2 * imag / DFT_SIZE;
    }
}

float FourierTransform_GetMag(FourierTransform* fourierTransform, uint32_t index)
{
    return sqrtf(powf(fourierTransform->real[index], 2) + powf(fourierTransform->imag[index], 2));
}

float FourierTransform_GetPhase(FourierTransform* fourierTransform, uint32_t index)
{
    return atanf(fourierTransform->imag[index] / fourierTransform->real[index]);
}

void FourierTransform_GetMagBin(FourierTransform* fourierTransform, float* out_magBin)
{
    for (uint32_t i = 0; i < DFT_SIZE; i++)
    {
        out_magBin[i] = FourierTransform_GetMag(fourierTransform, i);
    }
}