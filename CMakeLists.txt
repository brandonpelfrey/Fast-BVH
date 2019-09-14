cmake_minimum_required(VERSION 3.00)
project(Fast_BVH)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-msse3")

add_executable(Fast_BVH RayTracerTest.cpp BVH.cpp BBox.cpp)