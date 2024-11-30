#include "Texture.hpp"

namespace Minecraft::OpenGL
{
    Texture::Texture(const TextureData &data,int width,int height,int channels): mData(data), mWidth(width), mHeight(height), mChannels(channels)
    {
        
    }
    Texture::~Texture()
    {
        glDeleteTextures(1,&mTexture);
    }
    int Texture::width() const
    {
        return mWidth;
    }
    int Texture::height() const
    {
        return mHeight;
    }
    int Texture::channels() const
    {
        return mChannels;
    }
    void Texture::bind() const
    {
        glBindTexture(GL_TEXTURE_2D,mTexture);
    }
    void Texture::bind(GLuint unit) const
    {
        glBindTextureUnit(unit,mTexture);
    }
    void Texture::load()
    {
        glGenTextures(1,&mTexture);
        bind();
        // TODO: make this changable with methods
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,mWidth,mHeight,0,GL_RGBA,GL_FLOAT,mData.data());
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}