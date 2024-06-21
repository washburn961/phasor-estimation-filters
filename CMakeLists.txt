# Top-level CMakeLists.txt

cmake_minimum_required(VERSION 3.8)

project(main LANGUAGES C)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

add_subdirectory(phasorfilters)
add_subdirectory(gnuplot_i)

# Add the executable
add_executable(main main.c)

# Link the library to the executable
target_link_libraries(main PRIVATE phasorfilters)
target_link_libraries(main PRIVATE gnuplot_i)
#set(ENV{PATH} "$ENV{PATH};C:/Program Files/gnuplot/bin")

if (MSVC)
    add_compile_options(/wd4305)
elseif (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-Wno-conversion)
endif()
