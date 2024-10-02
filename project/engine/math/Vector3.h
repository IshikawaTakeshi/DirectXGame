#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;
<<<<<<< HEAD:MyMath/Vector3.h
};
=======

	Vector3 operator+=(const Vector3& v);
	Vector3 operator-=(const Vector3& v);
	Vector3 operator*=(float s);
	Vector3 operator/=(float s);
};

Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3 operator+(const Vector3& v);
Vector3 operator-(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v);
Vector3 operator*(float s, const Vector3& v);
Vector3 operator*(const Vector3& v, float s);
Vector3 operator/(float s, const Vector3& v);
Vector3 operator/(const Vector3& v, float s);
>>>>>>> GE3_08_01:project/engine/math/Vector3.h
