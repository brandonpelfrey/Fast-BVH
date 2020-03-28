#pragma once

#include <cmath>

namespace FastBVH {

struct Vector3 final {

  float x;
  float y;
  float z;
  float w = 1;

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

  Vector3 operator*(float b) const noexcept {
    return Vector3 {
      x * b,
      y * b,
      z * b,
      w * b
    };
  }

  Vector3 operator/(float b) const noexcept {
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
  float operator*(const Vector3& b) const noexcept {
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
  float& operator[](const unsigned int i) {
    return (&x)[i];
  }

  const float& operator[](const unsigned int i) const {
    return (&x)[i];
  }
};

// Component-wise min
inline Vector3 min(const Vector3& a, const Vector3& b) {
  return Vector3 {
    std::fmin(a.x, b.x),
    std::fmin(a.y, b.y),
    std::fmin(a.z, b.z),
    std::fmin(a.w, b.w)
  };
}

// Component-wise max
inline Vector3 max(const Vector3& a, const Vector3& b) {
  return Vector3 {
    std::fmax(a.x, b.x),
    std::fmax(a.y, b.y),
    std::fmax(a.z, b.z),
    std::fmax(a.w, b.w)
  };
}

// Length of a vector
inline float length(const Vector3& a) {
  return std::sqrt(a * a);
}

// Make a vector unit length
inline Vector3 normalize(const Vector3& in) {
  return in * (1.0f / length(in));
}

} // namespace FastBVH
