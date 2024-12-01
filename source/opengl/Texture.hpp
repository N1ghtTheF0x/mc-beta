#ifndef __MINECRAFT_FS_TEXTURE_HPP
#define __MINECRAFT_FS_TEXTURE_HPP

#include <glad/glad.h>
#include <vector>
#include <string>

namespace Minecraft::OpenGL
{
    class Texture;
    typedef std::vector<GLubyte> TextureData;
    typedef std::vector<Texture*> Textures;
    class Texture
    {
    private:
        GLuint mTexture;
        TextureData mData;
        int mWidth;
        int mHeight;
        int mChannels;
    public:
#ifdef _DEBUG
        static void EditorContent(Texture* texture);
        static void EditorContent(Textures& textures);
        static void Editor(Texture* texture,const char* name,bool* enabled = (bool*)0);
#endif
        Texture();
        Texture(const TextureData &data,int width,int height,int channels);
        int width() const;
        int height() const;
        int channels() const;
        void load();
        void unload();
        void bind() const;
        void bind(GLuint unit) const;
    };
}

#endif