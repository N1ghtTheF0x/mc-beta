#ifndef __MINECRAFT_MATH_VECTORS_HPP
#define __MINECRAFT_MATH_VECTORS_HPP

#include "Quaternion.hpp"
#include <algorithm>
#include <cmath>

namespace Minecraft::Math
{
    struct Vector3;
    struct Vector2
    {
        union {
            struct {
                float x;
                float y;
            };
            float data[2];
        };
        static Vector2 fromPoints(Vector2 a,Vector2 b)
        {
            return {b.x - a.x,b.y - a.x};
        }
        static Vector2 clamp(Vector2 v,Vector2 lo,Vector2 hi)
        {
            return {
                std::clamp(v.x,lo.x,hi.x),
                std::clamp(v.y,lo.y,hi.y)
            };
        }
        Vector2(): x(0.0f),y(0.0f) {}
        Vector2(float x,float y): x(x),y(y) {}
        Vector2(float value): Vector2(value,value) {}
        bool operator==(const Vector2& vec) const
        {
            return x == vec.x && y == vec.y;
        }
        Vector2& operator=(const Vector2& vec)
        {
            x = vec.x;
            y = vec.y;
            return *this;
        }
        Vector2 operator+(const Vector2& vec) const
        {
            return {
                x + vec.x,
                y + vec.y
            };
        }
        Vector2 operator-(const Vector2& vec) const
        {
            return {
                x - vec.x,
                y - vec.y
            };
        }
        Vector2 operator/(const Vector2& vec) const
        {
            return {
                x / vec.x,
                y / vec.y
            };
        }
        Vector2 operator*(float scalar) const
        {
            return {
                x * scalar,
                y * scalar
            };
        }
        float operator*(const Vector2& vec) const
        {
            return x*vec.x+y*vec.y;
        }
        float distance(const Vector2& vec) const
        {
            return std::pow(vec.x - x,2) + std::pow(vec.y - y,2);
        }
        float distanceSquared(const Vector2& vec) const
        {
            return std::sqrt(distance(vec));
        }
        float length() const
        {
            return std::sqrt(x*x+y*y);
        }
        Vector2 cartesianify() const
        {
            return {
                x * std::cos(y),
                x * std::sin(y)
            };
        }
        Vector2 polarify() const
        {
            return {
                length(),
                std::atan(y/x)
            };
        }
        Vector2 normalized() const
        {
            float l = length();
            return {
                x / l,
                y / l
            };
        }
    };
    struct Vector3
    {
        union {
            struct {
                float x;
                float y;
                float z;
            };
            float data[3];
        };
        static Vector3 fromPoints(Vector3 a,Vector3 b)
        {
            return {b.x - a.x,b.y - a.x,b.z - a.z};
        }
        static Vector3 clamp(Vector3 v,Vector3 lo,Vector3 hi)
        {
            return {
                std::clamp(v.x,lo.x,hi.x),
                std::clamp(v.y,lo.y,hi.y),
                std::clamp(v.z,lo.z,hi.z)
            };
        }
        Vector3(): x(0.0f),y(0.0f),z(0.0f) {}
        Vector3(float x,float y,float z): x(x),y(y),z(z) {}
        Vector3(float x,float y): Vector3(x,y,0.0f) {}
        Vector3(float value): Vector3(value,value,value) {}
        Vector3(const Quaternion& quat): Vector3(quat.x,quat.y,quat.z) {}
        bool operator==(const Vector3& vec) const
        {
            return x == vec.x && y == vec.y && z == vec.z;
        }
        Vector3& operator=(const Vector3& vec)
        {
            x = vec.x;
            y = vec.y;
            z = vec.z;
            return *this;
        }
        Vector3 operator+(const Vector3& vec) const
        {
            return {
                x + vec.x,
                y + vec.y,
                z + vec.z
            };
        }
        Vector3 operator-(const Vector3& vec) const
        {
            return {
                x - vec.x,
                y - vec.y,
                z - vec.z
            };
        }
        Vector3 operator/(const Vector3& vec) const
        {
            return {
                x / vec.x,
                y / vec.y,
                z / vec.z
            };
        }
        Vector3 operator*(float scalar) const
        {
            return {
                x * scalar,
                y * scalar,
                z * scalar
            };
        }
        float operator*(const Vector3& vec) const
        {
            return x*vec.x+y*vec.y+z*vec.z;
        }
        float distance(const Vector3& vec) const
        {
            return std::pow(vec.x - x,2) + std::pow(vec.y - y,2) + std::pow(vec.z - z,2);
        }
        float distanceSquared(const Vector3& vec) const
        {
            return std::sqrt(distance(vec));
        }
        float length() const
        {
            return std::sqrt(x*x+y*y+z*z);
        }
        Vector3 normalized() const
        {
            float l = length();
            return {
                x / l,
                y / l,
                z / l
            };
        }
        Vector3 cross(const Vector3& vec) const
        {
            return {
                y*vec.z - z*vec.y,
                z*vec.x - x*vec.z,
                x*vec.y - y*vec.x
            };
        }
    };
}


#endif