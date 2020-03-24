#pragma once
#include <cmath>
#include <cstdint>
#include <string>
#include "Macros.h"

class DLLEXPORT Vector3 final
{
public:

    float x = 0, y = 0, z = 0;
    Vector3() = default;
    Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
    Vector3 operator + (const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
    Vector3 operator - (const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
    Vector3 operator * (const float& rhs) const { return Vector3(x * rhs, y * rhs, z * rhs); }
    Vector3 operator / (const float& rhs) const { return Vector3(x / rhs, y / rhs, z / rhs); }
    bool operator == (const Vector3& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
    bool operator != (const Vector3& rhs) const { return x != rhs.x || y != rhs.y || z != rhs.z; }
    Vector3& operator += (const Vector3& rhs) { return *this = *this + rhs; }
    Vector3& operator -= (const Vector3& rhs) { return *this = *this - rhs; }
    Vector3& operator *= (const float& rhs) { return *this = *this * rhs; }
    Vector3& operator /= (const float& rhs) { return *this = *this / rhs; }
    void Invert() { *this *= -1; }
    [[nodiscard]] float Length() const { return x * x + y * y + z * z; }
    [[nodiscard]] float SquaredLength() const { return std::sqrt(Length()); }
    [[nodiscard]] Vector3 Normalize() const { return *this * (1 / SquaredLength()); }
    [[nodiscard]] float Distance(const Vector3& rhs) const { return (*this - rhs).SquaredLength(); }
    [[nodiscard]] const char* ToString(const int d) const { static char buffer[128]; snprintf(buffer, 128, "[%.*f, %.*f, %.*f]", d, x, d, y, d, z); return buffer; }
    [[nodiscard]] bool Invalid() const { return x == 0 && y == 0 && z == 0; }
    static Vector3 zero() { return Vector3(); }
};