# Phasor Estimation Filters

This repository contains source code for DFT-based phasor estimation filters.

## Usage

The following steps show you how to run the example contained in main.c.

1. Clone the repository:

```git clone https://github.com/washburn961/phasor-estimation-filters.git```

2. Build and run using CMake:

```mkdir build```
```cd build```
```cmake ..```
```cmake --build .```
```main.exe```

Make sure you have gnuplot installed and added to PATH in order to run the example.

## Example

This is a plot showing an assymetrical fault current versus time:
!(vector_plot.png)

When running the example, it will compute the 8 samples per cycle DFT for all the current samples data and output the magnitude of the 60 Hz component versus time:
!(other_plot.png)
