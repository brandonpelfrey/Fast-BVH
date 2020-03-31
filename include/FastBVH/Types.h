#pragma once

#include <FastBVH/Config.h>

#ifndef __NVCC__
#include <cstddef>
#include <cstdint>
#endif

namespace FastBVH {

//! \brief This is a size type definition.
using Size = size_t;

//! \brief This is a type definition
//! for 32-bit signed integers.
using I32 = int32_t;

//! \brief This is a type definition
//! for 64-bit signed integers.
using I64 = int64_t;

//! \brief This is a type definition
//! for 32-bit unsigned integers.
using U32 = uint32_t;

//! \brief This is a type definition
//! for 64-bit unsigned integers.
using U64 = uint64_t;

#ifndef FASTBVH_NO_INT128

//! \brief This is a type definition
//! for 128-bit unsigned integers.
using U128 = unsigned __int128;

//! \brief This is a type definition
//! for 128-bit signed integers.
using I128 = __int128;

//! \brief Used for constructing 128-bit unsigned literal values.
//! \param high The higher 64-bits of the literal.
//! \param low The lower 64-bits of the literal.
//! \return The 128-bit literal value.
inline constexpr U128 literal128U(U64 high, U64 low) noexcept {
  return static_cast<U128>(high) << 64 | static_cast<U128>(low);
}

#endif  // FASTBVH_NO_INT128

//! \brief This class is used to map a floating point type
//! to an index type that is equal in size. This is to encourage
//! integer SIMD types to go along with their floating point equalivalents.
template <Size float_size>
struct AssociatedIndexType final {};

//! A specialization to map index types for 32-bit floats.
template <>
struct AssociatedIndexType<4> final {
  //! Indicates that 32-bit integers should be used with 32-bit floats.
  using Type = uint32_t;
};

//! A specialization to map index types for 64-bit floats.
template <>
struct AssociatedIndexType<8> final {
  //! Indicates that 64-bit integers should be used with 64-bit floats.
  using Type = uint64_t;
};

#ifndef FASTBVH_NO_INT128

//! A specialization to map index types for 128-bit floats.
template <>
struct AssociatedIndexType<16> final {
  //! The type to be used with a (possibly) 128-bit floating point type.
  //! Ideally, this would be a 128-bit integer. There's currently no
  //! standard integer type thats 128-bits in size.
  using Type = U128;
};

#endif  // FASTBVH_NO_INT128

}  // namespace FastBVH
