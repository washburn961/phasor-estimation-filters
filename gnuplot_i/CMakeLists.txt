# gnuplot_i/CMakeLists.txt

cmake_minimum_required(VERSION 3.8)

project(gnuplot_i LANGUAGES C)

file(GLOB SOURCES "src/*.c")
file(GLOB HEADERS "inc/*.h")

# Add the library
add_library(gnuplot_i STATIC ${SOURCES} ${HEADERS})

# Specify include directories for the library
target_include_directories(gnuplot_i PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
