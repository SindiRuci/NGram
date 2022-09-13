cmake_minimum_required(VERSION 3.23)
project(NGram_CLion)

set(CMAKE_CXX_STANDARD 11)

add_executable(NGram_CLion parallel_NGram.cpp sequential_NGram.cpp main.cpp parallel_main.h sequential_NGram.h)

# openMP configuration
FIND_PACKAGE(OpenMP REQUIRED)
if (OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()
