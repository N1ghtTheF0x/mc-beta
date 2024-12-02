#ifndef __MINECRAFT_INTERFACES_ITEXTURE_HPP
#define __MINECRAFT_INTERFACES_ITEXTURE_HPP

#include "../math/Color.hpp"

namespace Minecraft
{
    class ITexture
    {
    public:
        virtual size_t width() const = 0;
        virtual size_t height() const = 0;

        virtual void setPixel(size_t x,size_t y,Math::Color color) = 0;
        virtual Math::Color getPixel(size_t x,size_t y) const = 0;
    };
}

#endif