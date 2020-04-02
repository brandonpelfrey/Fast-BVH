#pragma once

#include <FastBVH/impl/Types.h>

namespace FastBVH {

namespace impl {

//! \brief Used for encoding 3D Morton values.
//! \param float_size The size of the floating point type being used.
template <Size float_size>
struct MortonEncoder final {};

//! \brief Used for encoding 32-bit 3D Morton values.
template <>
struct MortonEncoder<4> final {
  //! \brief Encodes a 3D Morton code into a 32-bit integer.
  //! \return An interleaved combination of @p x, @p y, and @p z.
  inline constexpr U32 operator()(U32 x, U32 y, U32 z) noexcept;

  //! \brief Inserts two zeros between each bit in @p n.
  inline static constexpr U32 expand(U32 n) noexcept;
};

//! \brief Used for encoding 64-bit 3D Morton values.
template <>
struct MortonEncoder<8> final {
  //! \brief Encodes a 3D Morton code into a 64-bit integer.
  //! \return An interleaved combination of @p x, @p y, and @p z.
  inline constexpr U64 operator()(U64 x, U64 y, U64 z) noexcept;

  //! \brief Inserts two zeros between each bit in @p n.
  inline static constexpr U64 expand(U64 n) noexcept;
};

#ifndef FASTBVH_NO_INT128

//! \brief Used for encoding 128-bit Morton codes.
template <>
struct MortonEncoder<16> final {
  //! \brief Encodes a 3D Morton code into a 128-bit integer.
  //! \return An interleaved combination of @p x, @p y, and @p z.
  inline constexpr U128 operator()(U128 x, U128 y, U128 z) noexcept;

  //! \brief Inserts two zeros between each bit in @p n.
  inline static constexpr U128 expand(U128 n) noexcept;
};

#endif  // FASTBVH_NO_INT128

} // namespace impl

} // namespace FastBVH

#include <FastBVH/impl/MortonCodec.inl>
