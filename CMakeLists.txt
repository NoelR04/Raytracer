cmake_minimum_required (VERSION 3.9)
project (geomtry)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-g -Wall -Wextra -Wpedantic -Wl,--stack,16777216)

include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

add_executable(math_test math_test.cc math.cc)
target_link_libraries(math_test gtest gtest_main)

add_executable(geometry_test geometry_test.cc math.cc geometry.cc)
target_link_libraries(geometry_test gtest gtest_main)

add_executable(raytracer.cc raytracer.cc math.cc geometry.cc)

