cmake_minimum_required(VERSION 3.1.3)

project(Fast_BVH LANGUAGES CXX)

option(FASTBVH_BUILD_EXAMPLES "Whether or not to build the example programs." ON)
option(FASTBVH_BUILD_TESTS    "Whether or not to build the unit tests." ON)

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

if(FASTBVH_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(FASTBVH_BUILD_EXAMPLES)

if(FASTBVH_BUILD_TESTS)
  add_subdirectory(tests)
  enable_testing()
endif(FASTBVH_BUILD_TESTS)
