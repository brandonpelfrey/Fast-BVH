#pragma once

#include <FastBVH/impl/MortonCodec.h>

namespace FastBVH {

namespace impl {

inline constexpr U32 MortonEncoder<4>::operator()(U32 x, U32 y, U32 z) noexcept {
  return (expand(x) << 2) | (expand(y) << 1) | expand(z);
}

inline constexpr U32 MortonEncoder<4>::expand(U32 n) noexcept {
  n = (n | (n << 16)) & 0x030000ff;
  n = (n | (n << 8)) & 0x0300f00f;
  n = (n | (n << 4)) & 0x030c30c3;
  n = (n | (n << 2)) & 0x09249249;
  return n;
}

inline constexpr U64 MortonEncoder<8>::operator()(U64 x, U64 y, U64 z) noexcept {
  return (expand(x) << 2) | (expand(y) << 1) | expand(z);
}

inline constexpr U64 MortonEncoder<8>::expand(U64 n) noexcept {
  n &= 0x1fffff;
  n = (n | n << 32) & 0x001f00000000ffff;
  n = (n | n << 16) & 0x001f0000ff0000ff;
  n = (n | n << 8) & 0x100f00f00f00f00f;
  n = (n | n << 4) & 0x10c30c30c30c30c3;
  n = (n | n << 2) & 0x1249249249249249;
  return n;
}

#ifndef FASTBVH_NO_INT128

inline constexpr U128 MortonEncoder<16>::operator()(U128 x, U128 y, U128 z) noexcept {
  return (expand(x) << 2) | (expand(y) << 1) | expand(z);
}

inline constexpr U128 MortonEncoder<16>::expand(U128 n) noexcept {
  n = (n | n << 64) & literal128U(0x000003ff00000000, 0x00000000ffffffffULL);
  n = (n | n << 32) & literal128U(0x000003ff00000000, 0xffff00000000ffffULL);
  n = (n | n << 16) & literal128U(0x030000ff0000ff00, 0x00ff0000ff0000ffULL);
  n = (n | n << 8) & literal128U(0x0300f00f00f00f00, 0xf00f00f00f00f00fULL);
  n = (n | n << 4) & literal128U(0x030c30c30c30c30c, 0x30c30c30c30c30c3ULL);
  n = (n | n << 2) & literal128U(0x0924924924924924, 0x9249249249249249ULL);
  return n;
}

#endif  // FASTBVH_NO_INT128

} // namespace impl

} // namespace FastBVH
