#ifndef __MINECRAFT_MATH_MATRICES_HPP
#define __MINECRAFT_MATH_MATRICES_HPP

#include "Vectors.hpp"
#include "Quaternion.hpp"

#include <cmath>

namespace Minecraft::Math
{
    struct Mat3
    {
        union {
            struct {
                float m11;float m12;float m13;
                float m21;float m22;float m23;
                float m31;float m32;float m33;
            };
            float data[9];
        };
        static Mat3 projection(float width,float height)
        {
            return {
                2/width,0,0,
                0,-2/height,0,
                -1,0,0
            };
        }
        Mat3(
            float m11,float m12,float m13,
            float m21,float m22,float m23,
            float m31,float m32,float m33
        ):
            m11(m11), m12(m12), m13(m13),
            m21(m21), m22(m22), m23(m23),
            m31(m31), m32(m32), m33(m33)
        {}
        Mat3():
            m11(1.0f), m12(0.0f), m13(0.0f),
            m21(0.0f), m22(1.0f), m23(0.0f),
            m31(0.0f), m32(0.0f), m33(1.0f)
        {}
        Mat3(Mat4 mat):
            m11(mat.m11), m12(mat.m12), m13(mat.m14),
            m21(mat.m21), m22(mat.m22), m23(mat.m24),
            m31(mat.m41), m32(mat.m42), m33(mat.m44)
        {}
        Mat3(Quaternion quat):
            Mat3(
                1-2*(quat.y*quat.y+quat.z*quat.z),2*(quat.x*quat.y-quat.w*quat.z),2*(quat.x*quat.z+quat.w*quat.y),
                2*(quat.x*quat.y+quat.w*quat.z),1-2*(quat.x*quat.x+quat.z*quat.z),2*(quat.y*quat.z-quat.w*quat.x),
                2*(quat.x*quat.z-quat.w*quat.y),2*(quat.y*quat.z+quat.w*quat.x),1-2*(quat.x*quat.x+quat.y*quat.y)
            )
        {}
        Mat3& operator=(Mat3 mat)
        {
            m11 = mat.m11, m12 = mat.m12, m13 = mat.m13;
            m21 = mat.m21, m22 = mat.m22, m23 = mat.m23;
            m31 = mat.m31, m32 = mat.m32, m33 = mat.m33;
            return *this;
        }
        bool operator==(Mat3 mat) const
        {
            return m11 == mat.m11 && m12 == mat.m12 && m13 == mat.m13 &&
                   m21 == mat.m21 && m22 == mat.m22 && m23 == mat.m23 &&
                   m31 == mat.m31 && m32 == mat.m32 && m33 == mat.m33;
        }
        Mat3 operator+(Mat3 mat) const
        {
            return {
                m11 + mat.m11, m12 + mat.m12, m13 + mat.m13,
                m21 + mat.m21, m22 + mat.m22, m23 + mat.m23,
                m31 + mat.m31, m32 + mat.m32, m33 + mat.m33
            };
        }
        Mat3 operator-(Mat3 mat) const
        {
            return {
                m11 - mat.m11, m12 - mat.m12, m13 - mat.m13,
                m21 - mat.m21, m22 - mat.m22, m23 - mat.m23,
                m31 - mat.m31, m32 - mat.m32, m33 - mat.m33
            };
        }
        Mat3 operator*(float scalar) const
        {
            return {
                m11 * scalar, m12 * scalar, m13 * scalar,
                m21 * scalar, m22 * scalar, m23 * scalar,
                m31 * scalar, m32 * scalar, m33 * scalar
            };
        }
        Mat3 operator*(Mat3 mat) const
        {
            return {
                mat.m11 * m11 + mat.m12 * m21 + mat.m13 * m31,
                mat.m11 * m12 + mat.m12 * m22 + mat.m13 * m32,
                mat.m11 * m13 + mat.m12 * m23 + mat.m13 * m33,

                mat.m21 * m11 + mat.m22 * m21 + mat.m23 * m31,
                mat.m21 * m12 + mat.m22 * m22 + mat.m23 * m32,
                mat.m21 * m13 + mat.m22 * m23 + mat.m23 * m33,

                mat.m31 * m11 + mat.m32 * m21 + mat.m33 * m31,
                mat.m31 * m12 + mat.m32 * m22 + mat.m33 * m32,
                mat.m31 * m13 + mat.m32 * m23 + mat.m33 * m33
            };
        }
        Vector2 operator*(Vector2 vec) const
        {
            Vector2 v = {
                vec.x * m11 + vec.y * m12 + m13,
                vec.x * m21 + vec.y * m22 + m23
            };
            float w = vec.x * m31 + vec.y * m32 + m33;
            if(w != 0)
                return v / w;
            return v;
        }
        Mat3 translate(float x,float y) const
        {
            return operator*({
                1.0f,0.0f,0.0f,
                0.0f,1.0f,0.0f,
                x,y,1
            });
        }
        Mat3 translate(Vector2 vec) const
        {
            return operator*({
                1.0f,0.0f,0.0f,
                0.0f,1.0f,0.0f,
                vec.x,vec.y,1
            });
        }
        Mat3 rotate(float angle) const
        {
            float c = std::cos(angle);
            float s = std::sin(angle);
            return operator*({
                c,-s,0,
                s,c,0,
                0,0,1
            });
        }
        Mat3 scale(float x,float y) const
        {
            return operator*({
                x,0,0,
                0,y,0,
                0,0,1
            });
        }
        Mat3 scale(float x) const
        {
            return scale(x,x);
        }
        Mat3 scale(Vector2 vec) const
        {
            return operator*({
                vec.x,0,0,
                0,vec.y,0,
                0,0,1
            });
        }
        float determinant() const
        {
            return m11 * m22 * m33 - m32 * m23 -
                   m12 * m21 * m33 - m23 * m31 +
                   m13 * m21 * m32 - m22 * m31;
        }
        Mat3 inverse() const
        {
            float det = determinant();
            return {
                (m22 * m33 - m32 * m23) * det,(m13 * m32 - m12 * m33) * det,(m12 * m23 - m13 * m22) * det,
                (m23 * m31 - m21 * m33) * det,(m11 * m33 - m13 * m31) * det,(m21 * m13 - m11 * m23) * det,
                (m21 * m32 - m31 * m22) * det,(m31 * m12 - m11 * m32) * det,(m11 * m22 - m21 * m12) * det
            };
        }
    };
    struct Mat4
    {
        union {
            struct {
                float m11;float m12;float m13;float m14;
                float m21;float m22;float m23;float m24;
                float m31;float m32;float m33;float m34;
                float m41;float m42;float m43;float m44;
            };
            float data[16];
        };
        Mat4(
            float m11,float m12,float m13,float m14,
            float m21,float m22,float m23,float m24,
            float m31,float m32,float m33,float m34,
            float m41,float m42,float m43,float m44
        ):
            m11(m11), m12(m12), m13(m13), m14(m14),
            m21(m21), m22(m22), m23(m23), m24(m24),
            m31(m31), m32(m32), m33(m33), m34(m34),
            m41(m41), m42(m42), m43(m43), m44(m44)
        {}
        Mat4():
            m11(1.0f), m12(0.0f), m13(0.0f), m14(0.0f),
            m21(0.0f), m22(1.0f), m23(0.0f), m24(0.0f),
            m31(0.0f), m32(0.0f), m33(1.0f), m34(0.0f),
            m41(0.0f), m42(0.0f), m43(0.0f), m44(1.0f)
        {}
        Mat4(Mat3 mat):
            m11(mat.m11), m12(mat.m12), m13(mat.m13), m14(0.0f),
            m21(mat.m21), m22(mat.m22), m23(mat.m23), m24(0.0f),
            m31(mat.m31), m32(mat.m32), m33(mat.m33), m34(0.0f),
            m41(0.0f), m42(0.0f), m43(0.0f), m44(1.0f)
        {}
        Mat4(Quaternion quat):
            Mat4(
                1-2*(quat.y*quat.y+quat.z*quat.z),2*(quat.x*quat.y-quat.w*quat.z),2*(quat.x*quat.z+quat.w*quat.y),0,
                2*(quat.x*quat.y+quat.w*quat.z),1-2*(quat.x*quat.x+quat.z*quat.z),2*(quat.y*quat.z-quat.w*quat.x),0,
                2*(quat.x*quat.z-quat.w*quat.y),2*(quat.y*quat.z+quat.w*quat.x),1-2*(quat.x*quat.x+quat.y*quat.y),0,
                0,0,0,1
            )
        {}
        Mat4& operator=(Mat4 mat)
        {
            m11 = mat.m11, m12 = mat.m12, m13 = mat.m13, m14 = mat.m14;
            m21 = mat.m21, m22 = mat.m22, m23 = mat.m23, m24 = mat.m24;
            m31 = mat.m31, m32 = mat.m32, m33 = mat.m33, m34 = mat.m34;
            m41 = mat.m41, m42 = mat.m42, m43 = mat.m43, m44 = mat.m44;
            return *this;
        }
        bool operator==(Mat4 mat) const
        {
            return m11 == mat.m11 && m12 == mat.m12 && m13 == mat.m13 && m14 == mat.m14 &&
                   m21 == mat.m21 && m22 == mat.m22 && m23 == mat.m23 && m24 == mat.m24 &&
                   m31 == mat.m31 && m32 == mat.m32 && m33 == mat.m33 && m34 == mat.m34 &&
                   m41 == mat.m41 && m42 == mat.m42 && m43 == mat.m43 && m44 == mat.m44;
        }
        Mat4 operator+(Mat4 mat) const
        {
            return {
                m11 + mat.m11, m12 + mat.m12, m13 + mat.m13, m14 + mat.m14,
                m21 + mat.m21, m22 + mat.m22, m23 + mat.m23, m24 + mat.m24,
                m31 + mat.m31, m32 + mat.m32, m33 + mat.m33, m34 + mat.m34,
                m41 + mat.m41, m42 + mat.m42, m43 + mat.m43, m44 + mat.m44
            };
        }
        Mat4 operator-(Mat4 mat) const
        {
            return {
                m11 - mat.m11, m12 - mat.m12, m13 - mat.m13, m14 - mat.m14,
                m21 - mat.m21, m22 - mat.m22, m23 - mat.m23, m24 - mat.m24,
                m31 - mat.m31, m32 - mat.m32, m33 - mat.m33, m34 - mat.m34,
                m41 - mat.m41, m42 - mat.m42, m43 - mat.m43, m44 - mat.m44
            };
        }
        Mat4 operator*(float scalar) const
        {
            return {
                m11 * scalar, m12 * scalar, m13 * scalar, m14 * scalar,
                m21 * scalar, m22 * scalar, m23 * scalar, m24 * scalar,
                m31 * scalar, m32 * scalar, m33 * scalar, m34 * scalar,
                m41 * scalar, m42 * scalar, m43 * scalar, m44 * scalar
            };
        }
        Mat4 operator*(Mat4 mat) const
        {
            return {
                mat.m11 * m11 + mat.m12 * m21 + mat.m13 * m31 + mat.m14 * m41,
                mat.m11 * m12 + mat.m12 * m22 + mat.m13 * m32 + mat.m14 * m42,
                mat.m11 * m13 + mat.m12 * m23 + mat.m13 * m33 + mat.m14 * m43,
                mat.m11 * m14 + mat.m12 * m24 + mat.m13 * m34 + mat.m14 * m44,

                mat.m21 * m11 + mat.m22 * m21 + mat.m23 * m31 + mat.m24 * m41,
                mat.m21 * m12 + mat.m22 * m22 + mat.m23 * m32 + mat.m24 * m42,
                mat.m21 * m13 + mat.m22 * m23 + mat.m23 * m33 + mat.m24 * m43,
                mat.m21 * m14 + mat.m22 * m24 + mat.m23 * m34 + mat.m24 * m44,

                mat.m31 * m11 + mat.m32 * m21 + mat.m33 * m31 + mat.m34 * m41,
                mat.m31 * m12 + mat.m32 * m22 + mat.m33 * m32 + mat.m34 * m42,
                mat.m31 * m13 + mat.m32 * m23 + mat.m33 * m33 + mat.m34 * m43,
                mat.m31 * m14 + mat.m32 * m24 + mat.m33 * m34 + mat.m34 * m44,

                mat.m41 * m11 + mat.m42 * m21 + mat.m43 * m31 + mat.m44 * m41,
                mat.m41 * m12 + mat.m42 * m22 + mat.m43 * m32 + mat.m44 * m42,
                mat.m41 * m13 + mat.m42 * m23 + mat.m43 * m33 + mat.m44 * m43,
                mat.m41 * m14 + mat.m42 * m24 + mat.m43 * m34 + mat.m44 * m44
            };
        }
        Vector3 operator*(Vector3 vec) const
        {
            Vector3 v = {
                vec.x * m11 + vec.y * m12 + vec.z * m13 + m14,
                vec.x * m21 + vec.y * m22 + vec.z * m23 + m24,
                vec.x * m31 + vec.y * m32 + vec.z * m33 + m34
            };
            float w = vec.x * m41 + vec.y * m42 + vec.z * m43 + m44;
            if(w != 0)
                return v / w;
            return v;
        }
        Mat4 translate(float x,float y,float z) const
        {
            return operator*({
                1.0f,0.0f,0.0f,0.0f,
                0.0f,1.0f,0.0f,0.0f,
                0.0f,0.0f,1.0f,0.0f,
                x,y,z,1.0f,
            });
        }
        Mat4 translate(Vector3 vec) const
        {
            return operator*({
                1.0f,0.0f,0.0f,0.0f,
                0.0f,1.0f,0.0f,0.0f,
                0.0f,0.0f,1.0f,0.0f,
                vec.x,vec.y,vec.z,1.0f,
            });
        }
        Mat4 rotateX(float angle) const
        {
            float c = std::cos(angle);
            float s = std::sin(angle);
            return operator*({
                1,0,0,0,
                0,c,s,0,
                0,-s,c,0,
                0,0,0,1
            });
        }
        Mat4 rotateY(float angle) const
        {
            float c = std::cos(angle);
            float s = std::sin(angle);
            return operator*({
                c,0,-s,0,
                0,1,0,0,
                s,0,c,0,
                0,0,0,1
            });
        }
        Mat4 rotateZ(float angle) const
        {
            float c = std::cos(angle);
            float s = std::sin(angle);
            return operator*({
                c,s,0,0,
                -s,c,0,0,
                0,0,1,0,
                0,0,0,1
            });
        }
        Mat4 rotate(float x,float y,float z) const
        {
            return rotateX(x).rotateY(y).rotateZ(z);
        }
        Mat4 rotate(Vector3 vec) const
        {
            return rotateX(vec.x).rotateY(vec.y).rotateZ(vec.z);
        }
        Mat4 scale(float x,float y,float z) const
        {
            return operator*({
                x,0,0,0,
                0,y,0,0,
                0,0,z,0,
                0,0,0,1
            });
        }
        Mat4 scale(float x) const
        {
            return scale(x,x,x);
        }
        Mat4 scale(Vector3 vec) const
        {
            return operator*({
                vec.x,0,0,0,
                0,vec.y,0,0,
                0,0,vec.z,0,
                0,0,0,1
            });
        }
        Mat4 inverse() const
        {
            return {
                m11,m21,m31,0,
                m12,m22,m32,0,
                m13,m23,m33,0,
                -(m41*m11+m42*m21+m43*m31),
                -(m41*m12+m42*m22+m43*m32),
                -(m41*m13+m42*m23+m43*m33),
                1
            };
        }
    };
}

#endif