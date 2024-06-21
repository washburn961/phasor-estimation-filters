#ifndef GNUPLOT_I_H
#define GNUPLOT_I_H

#include <stdio.h>

FILE* gnuplot_pipe;

void gnuplot_init();
void gnuplot_close();
void gnuplot_cmd(const char* cmd);
void gnuplot_plot_xy(const float* x, const float* y, int n, const char* title, const char* output_file);

#endif // GNUPLOT_I_H
