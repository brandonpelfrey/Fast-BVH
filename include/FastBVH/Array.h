#pragma once

#include <FastBVH/Iterable.h>
#include <FastBVH/Memory.h>

namespace FastBVH {

//! \brief This is a dynamically sized array class,
//! suitable to work with either the standard C library
//! or the CUDA runtime library. On CPU targets, the
//! memory is allocated on the CPU memory. On GPU targets,
//! the memory is allocated on the CPU.
//
//! Currently, this is only suitable for POD types,
//! or types that don't require deconstructors.
//
//! \tparam T The element type of the array.
template <typename T>
class Array final {
  //! A pointer to the array elements.
  T* elements;

  //! \param The number of elements in the array.
  Size count;

 public:
  //! Constructs an empty array.
  constexpr Array() noexcept : elements(nullptr), count(0) {}

  //! Constructs an array with a certain amount
  //! of elements allocated.
  Array(Size c) {
    elements = allocateArray<T>(c);
    count = elements ? c : 0;
  }

  //! Moves the array data to a new element.
  //! \param other The variable to move the array data from.
  Array(Array&& other) noexcept {
    elements = other.elements;
    count = other.count;
    other.elements = nullptr;
    other.count = 0;
  }

  //! Releases the memory allocated by the array.
  ~Array() { freeArray<T>(elements, count); }

  //! Accesses an iterable container of the elements.
  //! \return An iterable container of the elements.
  Iterable<T> getElements() noexcept { return Iterable<T>(elements, count); }

  //! Accesses an iterable read-only container of the elements.
  //! \return An iterable read-only container of the elements.
  ConstIterable<T> getElements() const noexcept { return Iterable<T>(elements, count); }

  //! Indicates the number of elements in the array.
  //! \return The number of elements in the array.
  constexpr inline auto size() const noexcept { return count; }

  //! Accesses an element at a specific index.
  //! Does not perform bounds checking.
  //! \param index The index of the element to get.
  //! \return A const reference to the specified element.
  inline constexpr const T& operator[](Size index) const noexcept { return elements[index]; }

  //! Accesses an element at a specific index.
  //! Does not perform bounds checking.
  //! \param index The index of the element to get.
  //! \return A reference to the specified element.
  inline T& operator[](Size index) noexcept { return elements[index]; }

  Array(const Array& other) = delete;
  Array& operator=(const Array&) = delete;
  Array& operator=(Array&&) = delete;
};

}  // namespace FastBVH
