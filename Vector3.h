#pragma once
#include <cmath>

// Vector3 struct represents a 3D vector and provides common vector operations
struct Vector3 {
    float x, y, z; // Components of the vector

    // Constructor with default values
    Vector3(float X = 0, float Y = 0, float Z = 0) : x(X), y(Y), z(Z) {}

    // Vector addition
    Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }

    // Vector subtraction
    Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }

    // Scalar multiplication
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }

    // Scalar division
    Vector3 operator/(float s) const { return Vector3(x / s, y / s, z / s); }

    // Compound assignment operators
    Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vector3& operator-=(const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
    Vector3& operator/=(float s) { x /= s; y /= s; z /= s; return *this; }

    // Unary minus operator for negating the vector
    Vector3 operator-() const { return Vector3(-x, -y, -z); }

    // Returns the length (magnitude) of the vector
    float length() const { return std::sqrt(x * x + y * y + z * z); }

    // Returns a normalized (unit length) version of the vector
    Vector3 normalized() const { float len = length(); return (len > 0) ? (*this) / len : Vector3(0, 0, 0); }

    // Dot product between two vectors
    float dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }

    // Cross product between two vectors
    Vector3 cross(const Vector3& v) const {
        return Vector3(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }
};

// Scalar multiplication with scalar on the left
inline Vector3 operator*(float s, const Vector3& v) { return v * s; }
