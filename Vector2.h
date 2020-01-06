#pragma once
#include <math.h>

class Vector2
{
public:
    float x, y;

    Vector2()
    {
    }

    Vector2(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    Vector2 operator -(const Vector2& v)
    {
        return Vector2(x - v.x, y - v.y);
    }

    void operator -=(const Vector2& v)
    {
        x -= v.x;
        y -= v.y;
    }

    Vector2 operator +(const Vector2& v)
    {
        return Vector2(x + v.x, y + v.y);
    }

    Vector2 operator +(const float& v)
    {
        return Vector2(x + v, y + v);
    }

    Vector2 operator -(const float& v)
    {
        return Vector2(x - v, y - v);
    }

    Vector2 operator +(const int& v)
    {
        return Vector2(x + v, y + v);
    }

    Vector2 operator -(const int& v)
    {
        return Vector2(x - v, y - v);
    }

    void operator +=(const Vector2& v)
    {
        x += v.x;
        y += v.y;
    }

    Vector2 operator *(const Vector2& v)
    {
        return Vector2(x * v.x, y * v.y);
    }

    Vector2 operator *(const float& a)
    {
        return Vector2(x * a, y * a);
    }

    Vector2 operator *=(const float& a)
    {
        return Vector2(x * a, y * a);
    }

    Vector2 operator /(const float& a)
    {
        if (x != 0.0f) {
            return Vector2(x / a, y / a);
        }
        else {
            return Vector2(x, y);
        }
    }

    void operator /=(const Vector2& v)
    {
        x /= v.x;
        y /= v.y;
    }

    void operator /=(const float& a)
    {
        x /= a;
        y /= a;
    }

    bool operator ==(const Vector2& v)
    {
        return (v.x == x) && (v.y == y);
    }

    float getAngle(Vector2* point)
    {
        if (!point || !this)
            return 0;

        auto dot = point->x * this->x + point->y * this->y;      // dot product between[x1, y1] and [x2, y2]
        auto det = point->x * this->y - point->y * this->x;    // determinant
        float angle = atan2(det, dot); // atan2(y, x) or atan2(sin, cos)
        return angle;
    }

    float getDistance(Vector2* point)
    {
        return hypot(this->x - point->x, this->y - point->y);
    }
};