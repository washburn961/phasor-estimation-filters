#include <stdio.h>
#include <stdlib.h>
#include "gnuplot_i.h"
#include "fault_data.h"
#include "fourier_transform.h"
#include "ring_buffer.h"

SlidingBuffer buffer;
FourierTransform dft;

int main(void) {

    SlidingBuffer_Init(&buffer);
    FourierTransform_Init(&dft);

    // Define two vectors (arrays) of data
    int n = sizeof(phase_a) / sizeof(phase_a[0]);
    float* x = (float*)malloc(n * sizeof(float));
    float* mag = (float*)malloc(n * sizeof(float));
    float samples[DFT_SIZE] = {0};

    if (x == NULL) { return; }
    if (mag == NULL) { return; }

    for (int i = 0; i < n; i++)
    {
        x[i] = (float)i;

        SlidingBuffer_Write(&buffer, phase_b[i]);
        SlidingBuffer_GetSamples(&buffer, samples, DFT_SIZE);
        FourierTransform_Evaluate(&dft, samples, DFT_SIZE);

        mag[i] = FourierTransform_GetMag(&dft, 1);
    }

    // Use the new function to plot and open the result
    gnuplot_plot_xy(x, phase_b, n, "Time domain", "vector_plot.png");
    gnuplot_plot_xy(x, mag, n, "Phasor magnitude", "other_plot.png");
    //gnuplot_plot_xy(x, phase_b, n, "Vector Plot", "vector_plot.png");
    //gnuplot_plot_xy(x, phase_c, n, "Vector Plot", "vector_plot.png");

    free(x);

    return 0;
}
