#include "THD.h"

float THD(float* magnitudeBin, uint32_t binSize)
{
    float quadraticSum = 0;

    for (uint32_t i = 2; i < binSize; i++)
    {
        quadraticSum += powf(magnitudeBin[i], 2);
    }
    
    return sqrtf(quadraticSum) / magnitudeBin[1];
}