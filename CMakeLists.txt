project(FastBVH)

cmake_minimum_required(VERSION 3.9.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES BBox.cpp BVH.cpp)
set(GLOB HEADERS ./*.h)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
