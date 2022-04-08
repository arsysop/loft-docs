cmake_minimum_required(VERSION 3.0.0)
project(std_samples)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add_executable(first first.cpp)
# add_executable(fancy_ptr_with_errors fancy_ptr_with_errors.cpp)
add_executable(fancy_ptr
        fancy_ptr.cpp
        fancy_ptr.h
    )

add_executable(fancy_ptr_trace
        fancy_ptr.cpp
        fancy_ptr.h
        stacktrace.cpp
    )

