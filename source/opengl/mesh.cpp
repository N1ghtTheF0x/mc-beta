#include "Mesh.hpp"
#include "../fs/File.hpp"
#include <cmath>

namespace Minecraft::OpenGL
{
    Mesh::Mesh(const VertexData &data,const IndexData &indices,GLenum usage): mData(data), mIndices(indices), mUsage(usage)
    {
        
    }
    Mesh::Mesh(const VertexData &data,const IndexData &indices): Mesh(data,indices,GL_STATIC_DRAW)
    {

    }
    Mesh::~Mesh()
    {
        unload();
    }
    void Mesh::load()
    {
        glGenVertexArrays(1,&mVAO);
        glGenBuffers(1,&mVBO);
        glGenBuffers(1,&mEBO);
    }
    void Mesh::unload() const
    {
        glDeleteVertexArrays(1,&mVAO);
        glDeleteBuffers(1,&mVBO);
        glDeleteBuffers(1,&mEBO);
    }
    void Mesh::bind() const
    {
        glBindVertexArray(mVAO);
    }
    void Mesh::setTexture(size_t index,Texture& texture)
    {
        texture.load();
        mTextures.insert(mTextures.begin() + index,texture);
    }
    void Mesh::setTexture(size_t index,std::filesystem::path path)
    {
        Texture tex = FileSystem::readTexture(path);
        tex.load();
        setTexture(index,tex);
    }
    void Mesh::build() const
    {
        bind();
        glBindBuffer(GL_ARRAY_BUFFER,mVBO);
        glBufferData(GL_ARRAY_BUFFER,mData.size() * sizeof(VertexPayload),mData.data(),mUsage);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,mIndices.size() * sizeof(IndexPayload),mIndices.data(),mUsage);
        linkVertexAttributes();
    }
    void Mesh::linkVertexAttributes() const
    {
        size_t offset = 0;
        // Position
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(VertexPayload),(void*)offset);
        glEnableVertexAttribArray(0);
        offset += sizeof(VertexPayload::p);
        // Texture Coords (UV)
        glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(VertexPayload),(void*)offset);
        glEnableVertexAttribArray(1);
        offset += sizeof(VertexPayload::tex);
        // Vertex Color (RGBA)
        glVertexAttribPointer(2,4,GL_FLOAT,GL_FALSE,sizeof(VertexPayload),(void*)offset);
        glEnableVertexAttribArray(2);
        offset += sizeof(VertexPayload::color);
    }
    void Mesh::draw(const Shader &shader)
    {
        GLuint textureC = std::min((GLuint)mTextures.size(),(GLuint)GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
        for(GLuint texture = 0;texture < textureC;texture++)
        {
            Texture& tex = mTextures[texture];
            tex.bind(texture);
        }
        shader.use();
        bind();
        glDrawElements(GL_TRIANGLES,3 * mData.size(),GL_UNSIGNED_INT,0);
    }
    Mesh Mesh::createCube()
    {
        VertexData data;
        IndexData indices;

        // Front
        VertexPayload front[] = {
            {0.5f,0.5f,0.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f}, // top-right
            {0.5f,-0.5f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f}, // bottom-right
            {-0.5f,-0.5f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f}, // bottom-left
            {-0.5f,0.5f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,1.0f} // top-left
        };
        IndexPayload frontI[] = {
            {0,1,3},
            {1,2,3}
        };
        data.append_range(front);
        indices.append_range(frontI);

        return {data,indices};
    }
}