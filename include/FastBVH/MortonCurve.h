#pragma once

#include <FastBVH/Array.h>
#include <FastBVH/Vector3.h>

#include <limits>

namespace FastBVH {

//! \brief this class is used to indicate
//! the traits of a morton curve for a
//! specified floating point type size.
template <Size float_size>
struct MortonTraits final {};

//! \brief Traits for Morton curve
//! for 32-bit floats.
template <>
struct MortonTraits<4> final {
  //! \brief This is the Morton curve
  //! resolution for 32-bit floats.
  static constexpr float domain() noexcept {
    return 1024;
  }
};

//! \brief Traits for Morton curve
//! for 64-bit floats.
template <>
struct MortonTraits<8> final {
  //! \brief This is the Morton curve
  //! resolution for 64-bit floats.
  //! If the size of "double" is not
  //! 8 bytes, then this is not instantiated.
  static constexpr double domain() noexcept {
    return 2097152;
  }
};

//! \brief Traits for Morton curve
//! for 128-bit floats.
template <>
struct MortonTraits<16> final {
  //! \brief This is the Morton curve
  //! resolution for 128-bit floats.
  //! If the size of "long double" is not
  //! 16 bytes, then this is not instantiated.
  static constexpr long double domain() noexcept {
    return 4.398046511104e12;
  }
};

//! \brief Used for encoding 3D Morton values.
//! \param float_size The size of the floating point type being used.
template <Size float_size>
struct MortonEncoder final {};

//! \brief Used for encoding 32-bit 3D Morton values.
template <>
struct MortonEncoder<4> final {
  //! \brief Encodes a 3D Morton code into a 32-bit integer.
  //! \return An interleaved combination of @p x, @p y, and @p z.
  inline U32 operator () (U32 x, U32 y, U32 z) noexcept {
    return (expand(x) << 2) | (expand(y) << 1) | expand(z);
  }
  //! \brief Inserts two zeros between each bit in @p n.
  inline static constexpr U32 expand(U32 n) noexcept {
    n = (n | (n << 16)) & 0x030000ff;
    n = (n | (n <<  8)) & 0x0300f00f;
    n = (n | (n <<  4)) & 0x030c30c3;
    n = (n | (n <<  2)) & 0x09249249;
    return n;
  }
};

//! \brief Used for encoding 64-bit 3D Morton values.
template <>
struct MortonEncoder<8> final {
  //! \brief Encodes a 3D Morton code into a 64-bit integer.
  //! \return An interleaved combination of @p x, @p y, and @p z.
  inline U64 operator () (U64 x, U64 y, U64 z) noexcept {
    return (expand(x) << 2) | (expand(y) << 1) | expand(z);
  }
  //! \brief Inserts two zeros between each bit in @p n.
  inline static constexpr U64 expand(U64 n) noexcept {
    n &= 0x1fffff;
    n = (n | n << 32) & 0x001f00000000ffff;
    n = (n | n << 16) & 0x001f0000ff0000ff;
    n = (n | n << 8)  & 0x100f00f00f00f00f;
    n = (n | n << 4)  & 0x10c30c30c30c30c3;
    n = (n | n << 2)  & 0x1249249249249249;
    return n;
  }
};

#ifndef FASTBVH_NO_INT128

//! \brief Used for encoding 128-bit Morton codes.
template <>
struct MortonEncoder<16> final {
  //! \brief Encodes a 3D Morton code into a 128-bit integer.
  //! \return An interleaved combination of @p x, @p y, and @p z.
  inline U128 operator () (U128 x, U128 y, U128 z) noexcept {
    return (expand(x) << 2) | (expand(y) << 1) | expand(z);
  }
  //! \brief Inserts two zeros between each bit in @p n.
  inline static constexpr U128 expand(U128 n) noexcept {
    n &= 0x3ffffffffff;
    n = (n | n << 64) & literal128U(0x000003ff00000000, 0x00000000ffffffffULL);
    n = (n | n << 32) & literal128U(0x000003ff00000000, 0xffff00000000ffffULL);
    n = (n | n << 16) & literal128U(0x030000ff0000ff00, 0x00ff0000ff0000ffULL);
    n = (n | n << 8)  & literal128U(0x0300f00f00f00f00, 0xf00f00f00f00f00fULL);
    n = (n | n << 4)  & literal128U(0x030c30c30c30c30c, 0x30c30c30c30c30c3ULL);
    n = (n | n << 2)  & literal128U(0x0924924924924924, 0x9249249249249249ULL);
    return n;
  }
};

#endif // FASTBVH_NO_INT128

//! \brief Used for computing a Morton space filling curve
//! to be used in the construction of a BVH.
//! \tparam Float The floating point type of the curve coordinates.
template <typename Float>
class MortonCurve final {
public:
  //! A type definition for a Morton code.
  //! This is usually going to end up being a
  //! 32-bit or 64-bit unsigned integer.
  using Code = typename AssociatedIndexType<sizeof(Float)>::Type;
  //! Generates a series of Morton codes for a set of primitives.
  //! \tparam Primitive The type of the primitive to generate the codes for.
  //! \param primitives The array of primitives to generate the codes for.
  //! \param box_converter Used to convert the primitives into their bounding boxes.
  template <typename Primitive, typename BoxConverter>
  Array<Code> operator () (const ConstIterable<Primitive>& primitives, BoxConverter box_converter) {

    Array<Float> x(primitives.size());
    Array<Float> y(primitives.size());
    Array<Float> z(primitives.size());

    Vector3<Float> center_min = {
      std::numeric_limits<Float>::infinity(),
      std::numeric_limits<Float>::infinity(),
      std::numeric_limits<Float>::infinity()
    };

    Vector3<Float> center_max = {
      -std::numeric_limits<Float>::infinity(),
      -std::numeric_limits<Float>::infinity(),
      -std::numeric_limits<Float>::infinity()
    };

    auto count = primitives.size();

    for (decltype(count) i = 0; i < count; i++) {

      auto box = box_converter(primitives[i]);

      auto center = box.getCenter();

      center_min = min(center_min, center);
      center_max = max(center_max, center);

      x[i] = center.x;
      y[i] = center.y;
      z[i] = center.z;
    }

    auto domain = (center_max - center_min);

    auto morton_domain = MortonTraits<sizeof(Float)>::domain();

    auto x_factor = morton_domain / domain.x;
    auto y_factor = morton_domain / domain.y;
    auto z_factor = morton_domain / domain.z;

    Array<Code> codes(primitives.size());

    MortonEncoder<sizeof(Float)> codec;

    auto min = [](auto a, auto b) {
      return (a < b) ? a : b;
    };

    for (decltype(count) i = 0; i < count; i++) {

      auto x_code = Code(((x[i] - center_min.x) * x_factor));
      auto y_code = Code(((y[i] - center_min.y) * y_factor));
      auto z_code = Code(((z[i] - center_min.z) * z_factor));

      x_code = min(x_code, morton_domain - 1);
      y_code = min(y_code, morton_domain - 1);
      z_code = min(z_code, morton_domain - 1);

      codes[i] = codec(x_code, y_code, z_code);
    }

    return codes;
  }
};

} // namespace FastBVH
