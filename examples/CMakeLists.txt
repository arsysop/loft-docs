cmake_minimum_required(VERSION 3.20)
project(std_samples)

set(CMAKE_CXX_STANDARD 14)

add_executable(first first.cpp)
add_executable(fancy_ptr_with_errors fancy_ptr_with_errors.cpp)
add_executable(fancy_ptr_dump fancy_ptr.cpp fancy_ptr.h )

