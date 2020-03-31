#pragma once

#include <FastBVH/impl/Types.h>

#include <cstdlib>

namespace FastBVH {

namespace impl {

//! Allocates memory on the device.
//! \param size The number of bytes to allocate.
//! \return A pointer to the allocated memory.
inline void* allocateDeviceMemory(Size size) {
  return std::malloc(size);
}

//! Releases memory allocated by a call to @ref allocateDeviceMemory.
//! \param ptr A pointer returned by @ref allocateDeviceMemory.
//! This may be a null pointer, in which case the function returns early.
inline void freeDeviceMemory(void* ptr) {
  std::free(ptr);
}

//! Allocates an array of elements.
//! Currently, this is only suitable for POD types,
//! or types that don't require deconstructors.
//! \tparam T The type of the array elements.
//! \param element_count The number of elements to allocate memory for.
//! \return A pointer to the allocated memory.
template <typename T>
T* allocateArray(Size element_count) {
  return (T*)allocateDeviceMemory(element_count * sizeof(T));
}

//! Releases memory allocated by @ref allocateArray.
//! \tparam T The element type of the array.
//! \param elements A pointer to the elements to free.
template <typename T>
void freeArray(T* elements, Size) {
  freeDeviceMemory(elements);
}

} // namespace impl

}  // namespace FastBVH
