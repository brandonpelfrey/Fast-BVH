#pragma once

#include <cmath>

namespace FastBVH {

template <typename Float = float>
struct Vector3 final {

  Float x;
  Float y;
  Float z;
  Float w = 1;

  Vector3 operator+(const Vector3& b) const noexcept {
    return Vector3 {
      x + b.x,
      y + b.y,
      z + b.z,
      w + b.w
    };
  }

  Vector3 operator-(const Vector3& b) const noexcept {
    return Vector3 {
      x - b.x,
      y - b.y,
      z - b.z,
      w - b.w
    };
  }

  Vector3 operator*(Float b) const noexcept {
    return Vector3 {
      x * b,
      y * b,
      z * b,
      w * b
    };
  }

  Vector3 operator/(Float b) const noexcept {
    return Vector3 {
      x / b,
      y / b,
      z / b,
      w / b
    };
  }

  Vector3 cmul(const Vector3& b) const noexcept {
    return Vector3 {
      x * b.x,
      y * b.y,
      z * b.z,
      w * b.w
    };
  }

  Vector3 cdiv(const Vector3& b) const noexcept {
    return Vector3 {
      x / b.x,
      y / b.y,
      z / b.z,
      w / b.w
    };
  }

  // dot (inner) product
  Float operator*(const Vector3& b) const noexcept {
    return (x * b.x)
         + (y * b.y)
         + (z * b.z);
  }

  // Cross Product
  Vector3 operator^(const Vector3& b) const noexcept {
    return Vector3 {
      (y * b.z) - (z * b.y),
      (z * b.x) - (x * b.z),
      (x * b.y) - (y * b.x),
    };
  }

  Vector3 operator / (const Vector3& b) const noexcept {
    return Vector3 {
      x / b.x,
      y / b.y,
      z / b.z,
      w / b.w
    };
  }

  // Handy component indexing
  inline Float& operator[](const unsigned int i) {
    return (&x)[i];
  }

  inline const Float& operator[](const unsigned int i) const noexcept {
    return (&x)[i];
  }
};

// Component-wise min
template <typename Float>
inline Vector3<Float> min(const Vector3<Float>& a,
                          const Vector3<Float>& b) noexcept {

  return Vector3<Float> {
    std::fmin(a.x, b.x),
    std::fmin(a.y, b.y),
    std::fmin(a.z, b.z),
    std::fmin(a.w, b.w)
  };
}

// Component-wise max
template <typename Float>
inline Vector3<Float> max(const Vector3<Float>& a,
                          const Vector3<Float>& b) noexcept {

  return Vector3<Float> {
    std::fmax(a.x, b.x),
    std::fmax(a.y, b.y),
    std::fmax(a.z, b.z),
    std::fmax(a.w, b.w)
  };
}

// Length of a vector
template <typename Float>
inline Float length(const Vector3<Float>& a) {
  return std::sqrt(a * a);
}

// Make a vector unit length
template <typename Float>
inline Vector3<Float> normalize(const Vector3<Float>& in) {
  return in * (1.0f / length(in));
}

} // namespace FastBVH
