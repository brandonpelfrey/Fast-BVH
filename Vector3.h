#ifndef Vector3_h
#define Vector3_h

#include <string>
#include <algorithm>
#include <cmath>
#include "Log.h"

// SSE Vector object
struct Vector3 {
	float x,y,z;

	Vector3() { }
	Vector3(float x, float y, float z) : x(x), y(y), z(z) { }

	Vector3 operator+(const Vector3& b) const { return Vector3(x+b.x, y+b.y, z+b.z); }
	Vector3 operator-(const Vector3& b) const { return Vector3(x-b.x, y-b.y, z-b.z); }
	Vector3 operator*(float b) const { return Vector3(x*b, y*b, z*b); }
	Vector3 operator/(float b) const { b = 1.f / b; return Vector3(x*b, y*b, z*b); }

 // Component-wise multiply and divide
 Vector3 cmul(const Vector3& b) const { return Vector3(x*b.x, y*b.y, z*b.z);	}
 Vector3 cdiv(const Vector3& b) const { return Vector3(x/b.x, y/b.y, z/b.z);	}

	// dot (inner) product
	float operator*(const Vector3& b) const { return x*b.x + y*b.y + z*b.z;	}

 // Cross Product	
	Vector3 operator^(const Vector3& b) const {
  return Vector3(
   y * b.z - z * b.y, 
   z * b.x - x * b.z, 
   x * b.y - y * b.x
   );
	}

 // Handy component indexing 
 float& operator[](const unsigned int i) { return (&x)[i]; }
	const float& operator[](const unsigned int i) const { return (&x)[i]; }
};

inline Vector3 operator*(float a, const Vector3& b)  { return b * a; }

// Component-wise min
inline Vector3 min(const Vector3& a, const Vector3& b) {
	return Vector3( std::min(a.x,b.x), std::min(a.y,b.y), std::min(a.z,b.z) ); 
}

// Component-wise max
inline Vector3 max(const Vector3& a, const Vector3& b) {
	return Vector3( std::max(a.x,b.x), std::max(a.y,b.y), std::max(a.z,b.z) ); 
}

// Length of a vector
inline float length(const Vector3& a) {
	return sqrtf(a*a);
}

// Make a vector unit length
inline Vector3 normalize(const Vector3& in) {
	return in / length(in);
}

#endif
