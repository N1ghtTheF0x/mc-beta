#ifndef __MINECRAFT_FS_TEXTURE_HPP
#define __MINECRAFT_FS_TEXTURE_HPP

#include <glad/glad.h>
#include <vector>
#include <string>

namespace Minecraft::OpenGL
{
    typedef std::vector<GLfloat> TextureData;
    class Texture
    {
    private:
        GLuint mTexture;
        TextureData mData;
        int mWidth;
        int mHeight;
        int mChannels;
    public:
        Texture(const TextureData &data,int width,int height,int channels);
        ~Texture();
        int width() const;
        int height() const;
        int channels() const;
        void load();
        void bind() const;
        void bind(GLuint unit) const;
    };
    typedef std::vector<Texture> Textures;
}

#endif