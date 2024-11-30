#ifndef __MINECRAFT_OPENGL_MESH_HPP
#define __MINECRAFT_OPENGL_MESH_HPP

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
    class Mesh
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
        Mesh(const VertexData &data,const IndexData &indices,GLenum usage);
        Mesh(const VertexData &data,const IndexData &indices);
        ~Mesh();

        void setTexture(size_t index,Texture& texture);
        void setTexture(size_t index,std::filesystem::path path);

        void build() const;
        void bind() const;
        void load();
        void unload() const;
        void draw(const Shader &shader);

        static Mesh createCube();
    };
}

#endif