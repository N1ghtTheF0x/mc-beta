#ifndef __MINECRAFT_MATH_QUATERNION_HPP
#define __MINECRAFT_MATH_QUATERNION_HPP

#include <cmath>
#include <numbers>
#include "Vectors.hpp"

namespace Minecraft::Math
{
    struct AxisAngle
    {
        Vector3 axis;
        float angle;
    };
    struct Quaternion
    {
        union {
            struct {
                float w;
                float x;
                float y;
                float z;
            };
            float data[4];
        };
        static Quaternion fromAxisAngle(Vector3 vec,float angle)
        {
            float angle2 = angle/2;
            float sin2 = std::sin(angle2);
            float cos2 = std::cos(angle2);
            float length = sin2/std::sqrt(vec.x*vec.x+vec.y*vec.y+vec.z*vec.z);
            return {
                cos2,vec.x * length,vec.y * length,vec.z * length
            };
        }
        static Quaternion fromAxisAngle(AxisAngle aa)
        {
            float angle2 = aa.angle/2;
            float sin2 = std::sin(angle2);
            float cos2 = std::cos(angle2);
            float length = sin2/std::sqrt(aa.axis.x*aa.axis.x+aa.axis.y*aa.axis.y+aa.axis.z*aa.axis.z);
            return {
                cos2,aa.axis.x * length,aa.axis.y * length,aa.axis.z * length
            };
        }
        static Quaternion fromEuler(float x,float y,float z)
        {
            float x2 = x/2, y2 = y/2, z2 = z/2;
            float cx = std::cos(x2), cy = std::cos(y2), cz = std::cos(z2);
            float sx = std::sin(x2), sy = std::sin(y2), sz = std::sin(z2);
            return {
                cx * cy * cz - sx * sy * sz,
                sx * cy * cz - sy * sz * cx,
                sy * cx * cz - sx * sz * cy,
                sx * sy * cz + sz * cx * cy 
            };
        }
        Quaternion(float w,float x,float y,float z): w(w), x(x), y(y), z(z) {}
        Quaternion(): Quaternion(0,0,0,0) {}
        Quaternion(float w,Vector3 vec): Quaternion(w,vec.x,vec.y,vec.z) {}
        Quaternion& operator=(Quaternion& quat)
        {
            w = quat.w;
            x = quat.x;
            y = quat.y;
            z = quat.z;
            return *this;
        }
        bool operator==(Quaternion& quat) const
        {
            return w == quat.w && x == quat.x && y == quat.y && z == quat.z;
        }
        Quaternion operator+(Quaternion& quat) const
        {
            return {
                w + quat.w,
                x + quat.x,
                y + quat.y,
                z + quat.z
            };
        }
        Quaternion operator-(Quaternion& quat) const
        {
            return {
                w - quat.w,
                x - quat.x,
                y - quat.y,
                z - quat.z
            };
        }
        Quaternion operator*(Quaternion& quat) const
        {
            return {
                w * quat.w - x * quat.x - y * quat.y - z * quat.z,
                w * quat.x + x * quat.w + y * quat.z - z * quat.y,
                w * quat.y + y * quat.w + z * quat.x - x * quat.z,
                w * quat.z + z * quat.w + x * quat.y - y * quat.x
            };
        }
        Vector3 operator*(Vector3& vec) const
        {
            float ix = w * vec.x + y * vec.y - z * vec.y;
            float iy = w * vec.y + z * vec.x - x * vec.z;
            float iz = w * vec.z + x * vec.y - y * vec.x;
            float iw = -w * vec.x - y * vec.y - z * vec.z;
            return {
                ix * w + iw * -x + iy * -z - iz * -y,
                iy * w + iw * -y + iz * -x - ix * -z,
                iz * w + iw * -z + ix * -y - iy * -x
            };
        }
        Quaternion operator*(float scalar) const
        {
            return {
                w * scalar,
                x * scalar,
                y * scalar,
                z * scalar
            };
        }
        Quaternion operator/(Quaternion& quat) const
        {
            float l = 1/length();
            return {
                (w * quat.w + x * quat.x + y * quat.y + z * quat.z) * l,
                (x * quat.w - w * quat.x - y * quat.z + z * quat.y) * l,
                (y * quat.w - w * quat.y - z * quat.x + x * quat.z) * l,
                (z * quat.w - w * quat.z - x * quat.y + y * quat.x) * l
            };
        }
        float length() const
        {
            return w*w+x*x+y*y+z*z;
        }
        float lengthSquared() const
        {
            return std::sqrt(length());
        }
        Quaternion normalize() const
        {
            float l = 1/lengthSquared();
            return {
                w * l,
                x * l,
                y * l,
                z * l
            };
        }
        float dot(Quaternion quat) const
        {
            return w*quat.w+x*quat.x+y*quat.y+z*quat.z;
        }
        Quaternion inverse() const
        {
            float l = 1/length();
            return {
                w * l,
                -x * l,
                -y * l,
                -z * l
            };
        }
        Quaternion conjugate() const
        {
            return {
                w,
                -x,
                -y,
                -z
            };
        }
        AxisAngle toAxisAngle() const
        {
            float sin2 = 1 - w * w;
            if(sin2 > std::numeric_limits<float>::epsilon())
                return {{x,y,z},0};
            float isin = 1/std::sqrt(sin2);
            float angle = 2*std::acos(w);
            return {{x * isin,y * isin,z * isin},angle};
        }
        Vector3 toEuler() const
        {
            auto asin = [](float t)
            {
                return (float)(t >= 1 ? std::numbers::pi/2 : (t <= -1 ? -std::numbers::pi/2 : std::asin(t)));
            };
            return {
                -std::atan2(2 * (y*z - w*x),1 - 2 * (x*x + y*y)),
                asin(2 * (x*z + w*y)),
                -std::atan2(2 * (x*y - w*z),1 - 2 * (y*y + z*z))
            };
        }
    };
}

#endif