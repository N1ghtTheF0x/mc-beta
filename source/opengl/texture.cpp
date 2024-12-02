#include "Texture.hpp"

#ifdef _DEBUG
    #include <imgui.h>
#endif

namespace Minecraft::OpenGL
{
    Texture::Texture(const TextureData &data,int width,int height,int channels): mData(data), mWidth(width), mHeight(height), mChannels(channels)
    {
        
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
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D,mTexture);
    }
    void Texture::unload()
    {
        glDeleteTextures(1,&mTexture);
    }
    void Texture::load()
    {
        glGenTextures(1,&mTexture);
        bind();
        // TODO: make this changable with methods
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,mWidth,mHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,mData.data());
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    Asset::Type Texture::type() const
    {
        return Asset::Type::Texture;
    }
#ifdef _DEBUG
    void Texture::EditorContent(TexturePtr& texture)
    {
        float zoom = 1.0f;
        ImGui::Text("Pointer: %x",texture->mTexture);
        ImGui::Text("Size: %dx%d",texture->mWidth,texture->mHeight);
        ImGui::SliderFloat("Zoom",&zoom,0.1f,20.0f);
        ImGui::Image(
            (ImTextureID)(intptr_t)texture->mTexture,
            ImVec2(texture->mWidth * zoom,texture->mHeight * zoom),
            ImVec2(0.0f,0.0f),
            ImVec2(1.0f,1.0f)
        );
    }
    void Texture::Editor(TexturePtr& texture,const char* name,bool* enabled)
    {
        ImGui::Begin(name,enabled);
            EditorContent(texture);
        ImGui::End();
    }
    void Texture::EditorContent(Textures& textures)
    {
        if(ImGui::CollapsingHeader("Textures"))
        {
            for(size_t i = 0;i < textures.size();i++)
            {
                TexturePtr& texture = textures.at(i);
                std::string texname = std::to_string(i);
                ImGui::PushID(i);
                    if(ImGui::CollapsingHeader(texname.c_str()))
                        EditorContent(texture);
                ImGui::PopID();
            }
        }
    }
#endif
}