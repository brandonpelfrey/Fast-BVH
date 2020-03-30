cmake_minimum_required(VERSION 3.1.3)

find_package(GTest)

if(NOT GTest_FOUND)
  return()
endif(NOT GTest_FOUND)

add_executable(FastBVH_UnitTests
  BuildStrategy.cxx)

target_link_libraries(FastBVH_UnitTests PRIVATE FastBVH GTest::GTest GTest::Main)

target_compile_options(FastBVH_UnitTests PRIVATE ${cxxflags})

set_target_properties(FastBVH_UnitTests PROPERTIES
  OUTPUT_NAME run_tests
  RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

add_test(NAME FastBVH_UnitTests COMMAND $<TARGET_FILE:FastBVH_UnitTests>)

enable_testing()
