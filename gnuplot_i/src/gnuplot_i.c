#include "gnuplot_i.h"

void gnuplot_init() {
    gnuplot_pipe = _popen("gnuplot -persist", "w");
    if (!gnuplot_pipe) {
        fprintf(stderr, "Error: Could not open gnuplot.\n");
    }
}

void gnuplot_close() {
    fprintf(gnuplot_pipe, "exit\n");
    _pclose(gnuplot_pipe);
}

void gnuplot_cmd(const char* cmd) {
    fprintf(gnuplot_pipe, "%s\n", cmd);
    fflush(gnuplot_pipe);
}

void gnuplot_plot_xy(const float* x, const float* y, int n, const char* title, const char* output_file) {
    // Write the data to a temporary file
    FILE* temp = fopen("data.tmp", "w");
    if (!temp) {
        fprintf(stderr, "Error: Could not open temporary file for writing.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(temp, "%f %f\n", x[i], y[i]);
    }
    fclose(temp);

    // Initialize gnuplot
    gnuplot_init();

    // Set up gnuplot commands to plot the data from the temporary file
    gnuplot_cmd("set terminal png");                // Set the terminal type to PNG
    gnuplot_cmd("set output 'vector_plot.png'");    // Set the output file
    gnuplot_cmd("set title 'Vector Plot'");         // Set the title of the plot
    gnuplot_cmd("set xlabel 'x'");                  // Set the label for the x-axis
    gnuplot_cmd("set ylabel 'y'");                  // Set the label for the y-axis
    gnuplot_cmd("plot 'data.tmp' with lines");      // Plot the data from the temporary file

    // Close gnuplot
    gnuplot_close();

    // Open the generated PNG file with the default image viewer
    system("start vector_plot.png");
}