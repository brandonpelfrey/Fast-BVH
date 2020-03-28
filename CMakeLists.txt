cmake_minimum_required(VERSION 3.1.3)

project(Fast_BVH LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(gnu_cxxflags -Wall -Wextra -Werror -Wfatal-errors)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  list(APPEND gnu_cxxflags -ffast-math)
endif(CMAKE_BUILD_TYPE STREQUAL "Release")

if((CMAKE_CXX_COMPILER_ID STREQUAL GNU) OR (CMAKE_CXX_COMPILER_ID MATCHES Clang))
  set(cxxflags ${gnu_cxxflags})
endif((CMAKE_CXX_COMPILER_ID STREQUAL GNU) OR (CMAKE_CXX_COMPILER_ID MATCHES Clang))

add_library(FastBVH INTERFACE)

target_include_directories(FastBVH INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(FastBVH_RayTracerTest RayTracerTest.cpp)

target_link_libraries(FastBVH_RayTracerTest PRIVATE FastBVH)

target_compile_options(FastBVH_RayTracerTest PRIVATE ${cxxflags})

set_target_properties(FastBVH_RayTracerTest PROPERTIES OUTPUT_NAME RayTracerTest)
