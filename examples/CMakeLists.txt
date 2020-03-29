cmake_minimum_required(VERSION 3.1.3)

# Use this function to add a new example to the project.
#   Parameters:
#     name: The name of the example.
#           This is also assigned as the executable name.
#           The target name is FastBVH_Example_${name} so
#           that parent CMake projects don't have name collisions.
function(add_example name)

  set(target FastBVH_Example_${name})

  add_executable(${target} ${ARGN})

  target_link_libraries(${target} PRIVATE FastBVH)

  target_compile_options(${target} PRIVATE ${cxxflags})

  set_target_properties(${target} PROPERTIES
    OUTPUT_NAME ${name}
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

endfunction(add_example name)

add_example(CubeOfSpheres CubeOfSpheres.cpp)

add_example(ObjFile
  ObjFile.cpp
  tiny_obj_loader.h
  tiny_obj_loader.cc)
