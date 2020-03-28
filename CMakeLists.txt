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

function(add_example name)

  set(target FastBVH_Example_${name})

  add_executable(${target} ${ARGN})

  target_link_libraries(${target} PRIVATE FastBVH)

  target_compile_options(${target} PRIVATE ${cxxflags})

  set_target_properties(${target} PROPERTIES OUTPUT_NAME ${name})

endfunction(add_example name)

add_example(Basic examples/Basic.cpp)
