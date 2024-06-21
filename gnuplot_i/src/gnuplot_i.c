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
    char cmd[256];

    snprintf(cmd, sizeof(cmd), "set terminal png");
    gnuplot_cmd(cmd);

    snprintf(cmd, sizeof(cmd), "set output '%s'", output_file);
    gnuplot_cmd(cmd);

    snprintf(cmd, sizeof(cmd), "set title '%s'", title);
    gnuplot_cmd(cmd);

    snprintf(cmd, sizeof(cmd), "set xlabel 'x'");
    gnuplot_cmd(cmd);

    snprintf(cmd, sizeof(cmd), "set ylabel 'y'");
    gnuplot_cmd(cmd);

    snprintf(cmd, sizeof(cmd), "plot 'data.tmp' with lines");
    gnuplot_cmd(cmd);

    // Close gnuplot
    gnuplot_close();
}