#ifndef __MINECRAFT_FS_TEXTURE_HPP
#define __MINECRAFT_FS_TEXTURE_HPP

#include "../assets/Asset.hpp"

#include <glad/glad.h>
#include <vector>
#include <string>

namespace Minecraft::OpenGL
{
    DECLARE_ASSET(Texture)
    typedef std::vector<GLubyte> TextureData;
    typedef std::vector<TexturePtr> Textures;
    class Texture : public Asset
    {
    private:
        GLuint mTexture;
        TextureData mData;
        int mWidth;
        int mHeight;
        int mChannels;
    public:
#ifdef _DEBUG
        static void EditorContent(TexturePtr& texture);
        static void EditorContent(Textures& textures);
        static void Editor(TexturePtr& texture,const char* name,bool* enabled = (bool*)0);
#endif
        Texture(const TextureData &data,int width,int height,int channels);

        virtual void load() override;
        virtual void unload() override;
        Asset::Type type() const override;

        int width() const;
        int height() const;
        int channels() const;

        void bind() const;
        void bind(GLuint unit) const;
    };
}

#endif