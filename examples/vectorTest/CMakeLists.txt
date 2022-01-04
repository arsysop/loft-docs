cmake_minimum_required(VERSION 3.14)
project(testvector)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_vector TestVector.cpp)

target_link_libraries(test_vector gtest_main)

add_subdirectory(Vector)

enable_testing()
include(GoogleTest)
gtest_discover_tests(test_vector)
