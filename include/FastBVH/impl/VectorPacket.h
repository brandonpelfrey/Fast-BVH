#pragma once

#include <FastBVH/Vector3.h>

#include <FastBVH/impl/Types.h>

namespace FastBVH {

namespace impl {

//! \brief This class is a packet of vectors,
//! optimized for cache efficiency and SoA calculations.
//
//! \tparam Number The number type of the vector packet.
//
//! \tparam dimensions The number of dimensions in this vector.
//
//! \tparam cache_lines The number of cache lines to use per component.
//! Use this according to how many cache is expected to be used in a loop.
//! If there is just a couple of instances of vector packets in a loop,
//! it would be okay to use more than one cache line per component, which
//! would maximize cache usage. If there's otherwise a lot of vector packet
//! instances or other data, this value would be more conservative.
//! The default value is one, which is extremely conservative.
template <typename Number, Size dimensions, Size cache_lines = 1>
struct alignas(cacheLineSize()) VectorPacket final {
  //! \brief The number of elements per component.
  //! This is optimized so that each component array
  //! fits into a single line of cache.
  static constexpr auto size() noexcept {
    return (cacheLineSize() * cache_lines) / sizeof(Number);
  }

  //! \brief Indicates the total amount of values in the vector.
  //! \return The total number of values in the vector packet.
  //! This is the product of the dimension count and dimension size.
  static constexpr auto valueCount() noexcept {
    return size() * dimensions;
  }

  //! \brief The values in the vector packet.
  //! This is organized so that values in one
  //! dimension appear sequentially, increasing
  //! the chances of them getting optimized for SIMD.
  Number values[dimensions * size()] {};

  //! \brief Converts a vector to another vector of a different number type.
  //! \tparam OtherNumber The other number type to convert to.
  //! \param other The vector to put the converted values into.
  template <typename OtherNumber>
  void convert(VectorPacket<OtherNumber, dimensions>& other) const noexcept;

  //! \brief Adds two vector packets.
  //! \return The sum between the two vectors.
  constexpr VectorPacket operator + (const VectorPacket& other) const noexcept;

  //! \brief Subtracts two vector packets.
  //! \return The difference between the two vectors.
  constexpr VectorPacket operator - (const VectorPacket& other) const noexcept;

  //! \brief Multiplies the entire vector packet by a single scalar value.
  //! \return A new vector with the multiplied components.
  constexpr VectorPacket operator * (Number n) const noexcept;

  //! \brief Accesses a specific dimension of the vector packet.
  //! This function does not perform bounds checking.
  //! \param dimension The dimension of the vector packet to access.
  //! \return A const-pointer to the start of the dimension values.
  constexpr const Number* operator [] (Size dimension) const noexcept {
    return &values[dimension * size()];
  }

  //! \brief Accesses a specific dimension of the vector packet.
  //! This function does not perform bounds checking.
  //! \param dimension The dimension of the vector packet to access.
  //! \return A pointer to the start of the dimension values.
  Number* operator [] (Size dimension) noexcept {
    return &values[dimension * size()];
  }
};

//! \brief Calculates the hadamard product between two vectors.
//! \return The hadamard product between the two vectors.
template <typename Number, Size dimensions, Size cache_lines>
constexpr auto hadamard(const VectorPacket<Number, dimensions, cache_lines>& a,
                        const VectorPacket<Number, dimensions, cache_lines>& b) noexcept
  -> VectorPacket<Number, dimensions, cache_lines>;

//! \brief Calculates the hadamard product between
/// a packet of vectors and a single vector.
template <typename Number, Size cache_lines>
constexpr auto hadamard(const VectorPacket<Number, 3, cache_lines>& a,
                        const Vector3<Number>& b) noexcept
  -> VectorPacket<Number, 3, cache_lines>;

//! \brief Puts a single vector into the packet.
//! \param packet The packet to put the vector into.
//! \param index The index within the packet to put the vector into.
//! \param vec The vector to put into the packet.
template <typename Number, Size cache_lines>
void pack(VectorPacket<Number, 3, cache_lines>& packet, Size index, const Vector3<Number>& vec) noexcept {
  packet[0][index] = vec.x;
  packet[1][index] = vec.y;
  packet[2][index] = vec.z;
}

template <typename Number, Size cache_lines>
auto unpack(const VectorPacket<Number, 3, cache_lines>& packet, Size index) noexcept {
  Vector3<Number> out;
  out.x = packet[0][index];
  out.y = packet[1][index];
  out.z = packet[2][index];
  return out;
};

//! \brief Subtracts a single vector from a packet of vectors.
template <typename Number, Size cache_lines>
constexpr auto operator - (const VectorPacket<Number, 3, cache_lines>& a,
                           const Vector3<Number>& b) noexcept
  -> VectorPacket<Number, 3, cache_lines>;

} // namespace impl

} // namespace FastBVH

#include <FastBVH/impl/VectorPacket.inl>
