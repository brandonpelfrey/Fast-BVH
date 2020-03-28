#pragma once

#include <cmath>

namespace FastBVH {

//! \brief A type-generic 3 dimensional vector.
//! Used for the representation of bounding volumes
//! as well as the representation of rays and intersections.
//! \tparam Float The type used for the vector components.
template <typename Float>
struct Vector3 final {

  //! The X component of the vector.
  Float x;
  //! The Y component of the vector.
  Float y;
  //! The Z component of the vector.
  Float z;
  //! This is an used component, used
  //! for padding and SSE compatibility.
  Float w = 1;

  //! Adds two vectors.
  Vector3 operator+(const Vector3& b) const noexcept {
    return Vector3 {
      x + b.x,
      y + b.y,
      z + b.z,
      w + b.w
    };
  }

  //! Subtracts two vectors.
  Vector3 operator-(const Vector3& b) const noexcept {
    return Vector3 {
      x - b.x,
      y - b.y,
      z - b.z,
      w - b.w
    };
  }

  //! Multiplies the vector by a scalar value.
  Vector3 operator*(Float b) const noexcept {
    return Vector3 {
      x * b,
      y * b,
      z * b,
      w * b
    };
  }

  //! Divides the vector by a scalar value.
  Vector3 operator/(Float b) const noexcept {
    return Vector3 {
      x / b,
      y / b,
      z / b,
      w / b
    };
  }

  //! Component-wise vector multiplication.
  //! This is also called the hadamard product.
  Vector3 cmul(const Vector3& b) const noexcept {
    return Vector3 {
      x * b.x,
      y * b.y,
      z * b.z,
      w * b.w
    };
  }

  //! Component-wise vector division.
  Vector3 cdiv(const Vector3& b) const noexcept {
    return Vector3 {
      x / b.x,
      y / b.y,
      z / b.z,
      w / b.w
    };
  }

  //! Computes the dot product between two vectors.
  Float operator*(const Vector3& b) const noexcept {
    return (x * b.x)
         + (y * b.y)
         + (z * b.z);
  }

  //! Computes the cross product of two vectors.
  Vector3 operator^(const Vector3& b) const noexcept {
    return Vector3 {
      (y * b.z) - (z * b.y),
      (z * b.x) - (x * b.z),
      (x * b.y) - (y * b.x),
    };
  }

  /// Component-wise vector division.
  Vector3 operator / (const Vector3& b) const noexcept {
    return Vector3 {
      x / b.x,
      y / b.y,
      z / b.z,
      w / b.w
    };
  }

  //! Accesses a vector component by its index.
  inline Float& operator[](const unsigned int i) {
    return (&x)[i];
  }

  //! Accesses a vector component by its index.
  inline const Float& operator[](const unsigned int i) const noexcept {
    return (&x)[i];
  }
};

//! Calculates all minimum values between two vectors.
//! \tparam Float The floating point type of the vector.
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

//! Calculates all maximum values between two vectors.
//! \tparam Float The floating point type of the vector.
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

//! Computes the length of a vector.
//! \tparam Float The floating point type of the vector.
//! \param a The vector to compute the length of.
//! \return The length of @p a.
template <typename Float>
inline Float length(const Vector3<Float>& a) noexcept {
  return std::sqrt(a * a);
}

//! Divides a vector by it's length, making its magnitude equal to one.
//! \tparam Float The floating point type of the vector.
//! \param in The vector to normalize.
//! \return The normalized copy of @p in.
template <typename Float>
inline Vector3<Float> normalize(const Vector3<Float>& in) noexcept {
  return in * (1.0f / length(in));
}

} // namespace FastBVH
