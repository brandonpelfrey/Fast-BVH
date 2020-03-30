#pragma once

#include <cstddef>

namespace FastBVH {

//! A container for storing an iterable, read-write, continuous array.
//! \tparam T The type of a single element in the array.
template <typename T>
class Iterable final {
  //! A pointer to the array elements.
  T* array;

  //! The number of elements in the container.
  std::size_t count;

 public:
  //! Constructs a new iterable instance.
  //! \param a The array to iterate.
  //! \param c The number of elements in the array.
  constexpr Iterable(T* a, std::size_t c) noexcept : array(a), count(c) {}

  //! Accesses the beginning pointer.
  //! This is useful in range-based for loops.
  inline auto begin() noexcept { return array; }

  //! Accesses the ending pointer.
  //! This is useful in range-based for loops.
  inline auto end() noexcept { return array + count; }

  //! Accesses the beginning const-pointer.
  //! This is useful in range-based for loops.
  inline auto begin() const noexcept { return array; }

  //! Accesses the ending const-pointer.
  //! This is useful in range-based for loops.
  inline auto end() const noexcept { return array + count; }

  //! Accesses an element at a specific index.
  auto& operator[](std::size_t i) noexcept { return array[i]; }

  //! Indicates the number of elements in the container.
  auto size() const noexcept { return count; }
};

//! A container for storing an iterable, read-only, continuous array.
//! \tparam T The type of a single element in the array.
template <typename T>
class ConstIterable final {
  //! A pointer to the array elements.
  const T* array;

  //! The number of elements in the array.
  std::size_t count;

 public:
  //! Constructs a new iterable instance.
  //! \param a The array to iterate.
  //! \param c The number of elements in the array.
  constexpr ConstIterable(const T* a, std::size_t c) noexcept : array(a), count(c) {}

  //! Constructs a read-only iterable from a read-write iterable.
  //! \param other The read-write iterable to get the data from.
  constexpr ConstIterable(const Iterable<T>& other) noexcept : array(other.begin()), count(other.size()) {}

  //! Accesses the beginning pointer.
  //! This is useful in range-based for loops.
  inline auto begin() const noexcept { return array; }

  //! Accesses the ending pointer.
  //! This is useful in range-based for loops.
  inline auto end() const noexcept { return array + count; }

  //! Accesses an element at a specific index.
  const auto& operator[](std::size_t i) const noexcept { return array[i]; }

  //! Indicates the number of elements in the container.
  auto size() const noexcept { return count; }
};

}  // namespace FastBVH
