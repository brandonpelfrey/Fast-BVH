#pragma once

#include <FastBVH/impl/VectorPacket.h>

namespace FastBVH {

namespace impl {

template <typename Number, Size dimensions, Size cache_lines>
template <typename OtherNumber>
void VectorPacket<Number, dimensions, cache_lines>::convert(VectorPacket<OtherNumber, dimensions>& other) const noexcept {
  for (Size i = 0; i < valueCount(); i++) {
    other.values[i] = OtherNumber(values[i]);
  }
}

template <typename Number, Size dimensions, Size cache_lines>
constexpr auto VectorPacket<Number, dimensions, cache_lines>::operator + (const VectorPacket& other) const noexcept -> VectorPacket {

  VectorPacket out;

  for (Size i = 0; i < valueCount(); i++) {
    out.values[i] = values[i] + other.values[i];
  }

  return out;
}

template <typename Number, Size dimensions, Size cache_lines>
constexpr auto VectorPacket<Number, dimensions, cache_lines>::operator - (const VectorPacket& other) const noexcept -> VectorPacket {

  VectorPacket out;

  for (Size i = 0; i < valueCount(); i++) {
    out.values[i] = values[i] - other.values[i];
  }

  return out;
}

template <typename Number, Size dimensions, Size cache_lines>
constexpr auto VectorPacket<Number, dimensions, cache_lines>::operator * (Number n) const noexcept -> VectorPacket {

  VectorPacket out;

  for (Size i = 0; i < valueCount(); i++) {
    out.values[i] = values[i] * n;
  }

  return out;
}

template <typename Number, Size dimensions, Size cache_lines>
constexpr auto hadamard(const VectorPacket<Number, dimensions, cache_lines>& a,
                        const VectorPacket<Number, dimensions, cache_lines>& b) noexcept -> VectorPacket<Number, dimensions, cache_lines> {

  VectorPacket<Number, dimensions, cache_lines> out;

  for (Size i = 0; i < VectorPacket<Number, dimensions>::valueCount(); i++) {
    out.values[i] = a.values[i] * b.values[i];
  }

  return out;
}

template <typename Number, Size cache_lines>
constexpr VectorPacket<Number, 3, cache_lines> hadamard(const VectorPacket<Number, 3, cache_lines>& a, const Vector3<Number>& b) noexcept {

  VectorPacket<Number, 3, cache_lines> out;

  for (Size i = 0; i < VectorPacket<Number, 3, cache_lines>::size(); i++) {
    out[0][i] = a[0][i] * b.x;
    out[1][i] = a[1][i] * b.y;
    out[2][i] = a[2][i] * b.z;
  }

  return out;
}

template <typename Number, Size cache_lines>
constexpr VectorPacket<Number, 3, cache_lines> operator - (const VectorPacket<Number, 3, cache_lines>& a, const Vector3<Number>& b) noexcept {

  VectorPacket<Number, 3, cache_lines> out;

  for (Size i = 0; i < VectorPacket<Number, 3, cache_lines>::size(); i++) {
    out[0][i] = a[0][i] - b.x;
    out[1][i] = a[1][i] - b.y;
    out[2][i] = a[2][i] - b.z;
  }

  return out;
}

} // namespace impl

} // namespace FastBVH
