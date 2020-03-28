cmake_minimum_required(VERSION 3.1.3)

project(Fast_BVH LANGUAGES CXX)

option(ENABLE_SSE3 "Enable the use of explicit SSE3 code" ON)

set(CMAKE_CXX_STANDARD 14)

if(ENABLE_SSE3)
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-msse3")
endif(ENABLE_SSE3)

add_library(Fast_BVH
  BVH.h
  BVH.cpp
  BBox.h
  BBox.cpp
  Vector3.h
  Stopwatch.h
  Log.h)

target_include_directories(Fast_BVH PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_options(Fast_BVH PRIVATE -Wall -Wextra -Werror -Wfatal-errors)

add_executable(Fast_BVH_RayTracerTest RayTracerTest.cpp)

target_link_libraries(Fast_BVH_RayTracerTest PRIVATE Fast_BVH)

set_target_properties(Fast_BVH_RayTracerTest PROPERTIES OUTPUT_NAME RayTracerTest)
