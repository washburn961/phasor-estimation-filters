# phasor-estimation-filters/CMakeLists.txt

cmake_minimum_required(VERSION 3.8)

project(phasorfilters LANGUAGES C)

file(GLOB SOURCES "src/*.c")
file(GLOB HEADERS "inc/*.h")

# Add the library
add_library(phasorfilters STATIC ${SOURCES} ${HEADERS} "src/sine_filter.c" "src/half_cycle_fourier_transform.c" "src/cosine_filter.c" "src/fourier_transform.c")


# Specify include directories for the library
target_include_directories(phasorfilters PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
