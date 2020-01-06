#pragma once
#include "vector3.h"

struct Matrix3x3
{
    float M11; //a
    float M12; //b
    float M13; //c
    float M21; //d
    float M22; //e
    float M23; //f
    float M31; //g
    float M32; //h
    float M33; //i
    Matrix3x3(const float _00, const float _01, const float _02, const float _10, const float _11, const float _12, const float _20, const float _21, const float _22)
        : M11(_00), M12(_02), M13(_02), M21(_10), M22(_12), M23(_12), M31(_20), M32(_21), M33(_22) {}

    Matrix3x3 Inverse()
    {
        Matrix3x3 result = Matrix3x3(0, 0, 0, 0, 0, 0, 0, 0, 0);
        float d11 = M22 * M33 + M23 * -M32;
        float d12 = M21 * M33 + M23 * -M31;
        float d13 = M21 * M32 + M22 * -M31;

        float det = M11 * d11 - M12 * d12 + M13 * d13;
        if (std::abs(det) == 0.0f)
        {
            return result;
        }

        det = 1.f / det;

        float d21 = M12 * M33 + M13 * -M32;
        float d22 = M11 * M33 + M13 * -M31;
        float d23 = M11 * M32 + M12 * -M31;

        float d31 = (M12 * M23) - (M13 * M22);
        float d32 = (M11 * M23) - (M13 * M21);
        float d33 = (M11 * M22) - (M12 * M21);

        result.M11 = +d11 * det; result.M12 = -d21 * det; result.M13 = +d31 * det;
        result.M21 = -d12 * det; result.M22 = +d22 * det; result.M23 = -d32 * det;
        result.M31 = +d13 * det; result.M32 = -d23 * det; result.M33 = +d33 * det;

        return result;
    }
};

class CameraBase
{
public:
    char pad_0000[13368]; //0x0000
    class Camera* camera_ptr; //0x3438
}; //Size: 0x3338

class Camera
{
public:
    char pad_0000[16]; //0x0000
    Vector3 pos; //0x0010
    Matrix3x3 mat; //0x001C
    float fov; //0x0040
}; //Size: 0x0044