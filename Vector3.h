#ifndef Vector3_h
#define Vector3_h

#include <string>
#include <cmath>
#include <emmintrin.h>
#include <pmmintrin.h>
#include "Log.h"

// SSE Vector object
struct Vector3 {
  // This is silly, but it still helps.
  union __attribute__((aligned(16))) {
    struct { float x,y,z,w; };
    __m128 m128;
  };

  Vector3() { }
  Vector3(float x, float y, float z, float w=0.f) : m128(_mm_set_ps(w,z,y,x)) { }
  Vector3(const __m128& m128) : m128(m128) { }

  Vector3 operator+(const Vector3& b) const { return _mm_add_ps(m128, b.m128); }
  Vector3 operator-(const Vector3& b) const { return _mm_sub_ps(m128, b.m128); }
  Vector3 operator*(float b) const { return _mm_mul_ps(m128, _mm_set_ps(b,b,b,b)); }
  Vector3 operator/(float b) const { return _mm_div_ps(m128, _mm_set_ps(b,b,b,b)); }

  // Component-wise multiply and divide
  Vector3 cmul(const Vector3& b) const { return _mm_mul_ps(m128, b.m128); }
  Vector3 cdiv(const Vector3& b) const { return _mm_div_ps(m128, b.m128); }

  // dot (inner) product
  float operator*(const Vector3& b) const {
    return x*b.x + y*b.y + z*b.z;
  }

  // Cross Product
  Vector3 operator^(const Vector3& b) const {
    return _mm_sub_ps(
        _mm_mul_ps(
          _mm_shuffle_ps(m128, m128, _MM_SHUFFLE(3, 0, 2, 1)), 
          _mm_shuffle_ps(b.m128, b.m128, _MM_SHUFFLE(3, 1, 0, 2))),
        _mm_mul_ps(
          _mm_shuffle_ps(m128, m128, _MM_SHUFFLE(3, 1, 0, 2)), 
          _mm_shuffle_ps(b.m128, b.m128, _MM_SHUFFLE(3, 0, 2, 1)))
        );
  }

  Vector3 operator/(const Vector3& b) const { return _mm_div_ps(m128, b.m128); }

  // Handy component indexing
  float& operator[](const unsigned int i) { return (&x)[i]; }
  const float& operator[](const unsigned int i) const { return (&x)[i]; }
};

inline Vector3 operator*(float a, const Vector3&b)  { return _mm_mul_ps(_mm_set1_ps(a), b.m128); }

// Component-wise min
inline Vector3 min(const Vector3& a, const Vector3& b) {
  return _mm_min_ps(a.m128, b.m128);
}

// Component-wise max
inline Vector3 max(const Vector3& a, const Vector3& b) {
  return _mm_max_ps(a.m128, b.m128);
}

// Length of a vector
inline float length(const Vector3& a) {
  return sqrtf(a*a);
}

// Make a vector unit length
inline Vector3 normalize(const Vector3& in) {
  Vector3 a = in;
  a.w = 0.f;

  __m128 D = a.m128;
  D = _mm_mul_ps(D, D);
  D = _mm_hadd_ps(D, D);
  D = _mm_hadd_ps(D, D);

  // 1 iteration of Newton-raphson -- Idea from Intel's Embree.
  __m128 r = _mm_rsqrt_ps(D);
  r = _mm_add_ps(
      _mm_mul_ps(_mm_set_ps(1.5f, 1.5f, 1.5f, 1.5f), r),
      _mm_mul_ps(_mm_mul_ps(_mm_mul_ps(D, _mm_set_ps(-0.5f, -0.5f, -0.5f, -0.5f)), r), _mm_mul_ps(r, r)));

  return _mm_mul_ps( a.m128, r );
}

#endif
