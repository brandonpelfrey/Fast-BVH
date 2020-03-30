cmake_minimum_required(VERSION 3.1.3)

find_package(Threads REQUIRED)

if(NOT (CMAKE_BUILD_TYPE STREQUAL Release))
  message(WARNING "Building benchmark without optimizations")
endif(NOT (CMAKE_BUILD_TYPE STREQUAL Release))

set(model_zip "${CMAKE_CURRENT_BINARY_DIR}/sponza.zip")

if(NOT EXISTS ${model_zip})

  message(STATUS "Downloading test model")

  file(DOWNLOAD "https://github.com/jimmiebergmann/Sponza/archive/master.zip" ${model_zip}
       EXPECTED_HASH SHA256=dad248561594124cb5399964a57c9759fe2415496421ff640497c45e84f58e2c)

endif(NOT EXISTS ${model_zip})

set(model_dir "${CMAKE_CURRENT_BINARY_DIR}/Sponza-master")

if(NOT IS_DIRECTORY ${model_dir})

  message(STATUS "Extracting test model")

  execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${model_zip}
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

endif(NOT IS_DIRECTORY ${model_dir})

set(model_path "${CMAKE_CURRENT_BINARY_DIR}/Sponza-master/sponza.obj")

if(MSVC)
  list(APPEND cxxflags /DMODEL_PATH=\"${model_path}\")
else(MSVC)
  list(APPEND cxxflags -DMODEL_PATH=\"${model_path}\")
endif(MSVC)

add_executable(FastBVH_benchmark main.cpp ../examples/tiny_obj_loader.cc)

target_compile_options(FastBVH_benchmark PRIVATE ${cxxflags})

target_link_libraries(FastBVH_benchmark PRIVATE FastBVH Threads::Threads)

target_include_directories(FastBVH_benchmark PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

set_target_properties(FastBVH_benchmark PROPERTIES
  OUTPUT_NAME run_benchmark
  RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
