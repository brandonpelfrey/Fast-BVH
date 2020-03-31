#pragma once

#include <FastBVH/Types.h>

#ifndef __NVCC__
#include <cstdlib>
#endif

namespace FastBVH {

//! Allocates memory on the device.
//! For CPU builds, this is similar to a call to 'malloc'.
//! For CUDA builds, this allocates memory on the GPU.
//! \param size The number of bytes to allocate.
//! \return A pointer to the allocated memory.
inline void* allocateDeviceMemory(Size size) {
#ifndef __NVCC__
  return std::malloc(size);
#else
  void* ptr = nullptr;
  auto success = (cudaMalloc(&ptr, size) == cudaSuccess);
  return success ? ptr : nullptr;
#endif
}

//! Releases memory allocated by a call to @ref allocateDeviceMemory.
//! \param ptr A pointer returned by @ref allocateDeviceMemory.
//! This may be a null pointer, in which case the function returns early.
inline void freeDeviceMemory(void* ptr) {
#ifndef __NVCC__
  std::free(ptr);
#else
  cudaFree(ptr);
#endif
}

//! Allocates an array of elements.
//! Currently, this is only suitable for POD types,
//! or types that don't require deconstructors.
//! \tparam T The type of the array elements.
//! \param element_count The number of elements to allocate memory for.
//! \return A pointer to the allocated memory.
template <typename T>
T* allocateArray(Size element_count) {
  return (T*) allocateDeviceMemory(element_count * sizeof(T));
}

//! Releases memory allocated by @ref allocateArray.
//! \tparam T The element type of the array.
//! \param elements A pointer to the elements to free.
template <typename T>
void freeArray(T* elements, Size) {
  freeDeviceMemory(elements);
}

} // namespace FastBVH 
