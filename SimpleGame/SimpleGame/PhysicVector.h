#pragma once
#include "stdafx.h"

template<typename Ty>
struct Vector2D {
	Ty x, y;

	Vector2D() : x(0), y(0) {}
	Vector2D(Ty X, Ty Y) : x(X), y(Y) {}
	template<typename Ty1>
	Vector2D(Ty1 X, Ty1 Y) : x(static_cast<Ty>(X)), y(static_cast<Ty>(Y)) {}

	Vector2D& operator=(const Ty(&other)[2]) { x = other[0]; y = other[1]; return *this; }
	Vector2D& operator=(const Vector2D& other) { x = other.x; y = other.y;  return *this; }

	bool operator==(const Vector2D& other) const { return { Length(other - *this) < 0.00000001f }; }
};

using Vector2i = Vector2D<int>;
using Vector2f = Vector2D<float>;

template<typename Ty> inline float Length(const Vector2D<Ty>& Vec) { return(sqrt(Vec.x * Vec.x + Vec.y * Vec.y)); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename Ty>
struct Vector3D {
	Ty x, y, z;

	Vector3D() : x(0), y(0), z(0) {}
	Vector3D(Ty X, Ty Y, Ty Z) : x(X), y(Y), z(Z) {}
	template<typename Ty1>
	Vector3D(Ty1 X, Ty1 Y, Ty1 Z) : x(static_cast<Ty>(X)), y(static_cast<Ty>(Y)), z(static_cast<Ty>(Z)) {}

	Vector3D& operator=(const Ty(&other)[3]) { x = other[0]; y = other[1]; z = other[2]; return *this; }
	Vector3D& operator=(const Vector3D& other) { x = other.x; y = other.y; z = other.z; return *this; }

	bool operator==(const Vector3D& other) const { return { Length(other - *this) < 0.00000001f }; }
};

using Vector3i = Vector3D<int>;
using Vector3f = Vector3D<float>;

template<typename Ty> inline float Length(const Vector3D<Ty>& Vec) { return(sqrt(Vec.x * Vec.x + Vec.y * Vec.y + Vec.z * Vec.z)); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename Ty>
struct ColorVector {
	Ty r, g, b, a;

	ColorVector() : r(0), g(0), b(0), a(0) {}
	ColorVector(Ty R, Ty G, Ty B, Ty A) : r(R), g(G), b(B), a(A) {}
	template<typename Ty1>
	ColorVector(Ty R, Ty G, Ty B, Ty A) : r(static_cast<Ty>(R)), g(static_cast<Ty>(G)), b(static_cast<Ty>(B)), a(static_cast<Ty>(A)) {}


	ColorVector& operator=(const Ty(&other)[4]) { r = other[0]; g = other[1]; b = other[2];  a = other[3]; return *this; }
	ColorVector& operator=(const ColorVector& other) { r = other.r; g = other.g; b = other.b; a = other.a; return *this; }

};

using Color = ColorVector<float>;