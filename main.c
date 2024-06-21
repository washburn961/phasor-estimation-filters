#include <stdio.h>
#include <stdlib.h>
#include "gnuplot_i.h"
#include "fault_data.h"

// Dummy sum function to be implemented in your other library
int sum(int a, int b) {
    return a + b;
}

int main(void) {
    // Define two vectors (arrays) of data
    int n = sizeof(phase_a) / sizeof(phase_a[0]);
    float *x = (float*)malloc(n * sizeof(float));

    if (x == NULL) { return; }

    for (int i = 0; i < n; i++)
    {
        x[i] = (float)i;
    }

    // Use the new function to plot and open the result
    gnuplot_plot_xy(x, phase_b, n, "Vector Plot", "vector_plot.png");
    //gnuplot_plot_xy(x, phase_b, n, "Vector Plot", "vector_plot.png");
    //gnuplot_plot_xy(x, phase_c, n, "Vector Plot", "vector_plot.png");

    free(x);

    // Print the sum
    printf("1 + 2 eh igual a: %u\n", sum(1, 2));

    return 0;
}
