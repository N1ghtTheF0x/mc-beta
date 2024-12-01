#ifndef __MINECRAFT_MATH_COLOR_HPP
#define __MINECRAFT_MATH_COLOR_HPP

namespace Minecraft::Math
{
    struct Color
    {
        union {
            struct {
                float red;
                float green;
                float blue;
                float alpha;
            };
            float data[4];
        };
#if _DEBUG
        static void EditorContent(Color& color);
#endif
        Color(float red,float green,float blue,float alpha):
            red(red), green(green), blue(blue), alpha(alpha)
        {}
        Color(float red,float green,float blue): Color(red,green,blue,1.0f) {}
        Color(float value,float alpha): Color(value,value,value,alpha) {}
        Color(float value): Color(value,value,value,0.0f) {}
        Color(): Color(1.0f,1.0f,1.0f,1.0f) {}
    };
}

#endif