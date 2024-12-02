#ifndef __MINECRAFT_OPENGL_MESH_HPP
#define __MINECRAFT_OPENGL_MESH_HPP

#include "../assets/Asset.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

#include <vector>
#include <glad/glad.h>
#include <filesystem>

namespace Minecraft::OpenGL
{
    struct VertexPayload
    {
        GLfloat p[3];
        GLfloat tex[2];
        GLfloat color[4];
    };
    typedef std::vector<VertexPayload> VertexData;
    struct IndexPayload
    {
        GLuint x;
        GLuint y;
        GLuint z;
    };
    typedef std::vector<IndexPayload> IndexData;
    DECLARE_ASSET(Mesh)
    class Mesh : public Asset
    {
    private:
        GLenum mUsage;
        GLuint mVAO;
        GLuint mVBO;
        VertexData mData;
        GLuint mEBO;
        IndexData mIndices;
        Textures mTextures;

        void linkVertexAttributes() const;
    public:
#ifdef _DEBUG
        static void Editor(MeshPtr& mesh,const char* name,bool* enabled = (bool*)0);
        static void EditorContent(MeshPtr& mesh);
#endif
        Mesh(const VertexData &data,const IndexData &indices,GLenum usage);
        Mesh(const VertexData &data,const IndexData &indices);

        virtual void load() override;
        virtual void unload() override;
        Asset::Type type() const override;

        TexturePtr& addTexture(TexturePtr& texture);

        void build() const;
        void bind() const;
        void draw(const Shader &shader);

        static Mesh createCube();
    };
}

#endif