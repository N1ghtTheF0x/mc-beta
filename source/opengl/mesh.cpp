#include "Mesh.hpp"
#include "../fs/File.hpp"
#include <cmath>

#ifdef _DEBUG
    #include <imgui.h>
#endif

namespace Minecraft::OpenGL
{
    Mesh::Mesh(const VertexData &data,const IndexData &indices,GLenum usage): mData(data), mIndices(indices), mUsage(usage)
    {
        
    }
    Mesh::Mesh(const VertexData &data,const IndexData &indices): Mesh(data,indices,GL_STATIC_DRAW)
    {

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
    void Mesh::addTexture(Texture* texture)
    {
        mTextures.push_back(texture);
        texture->load();
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
        GLuint textureC = std::min((GLuint)mTextures.size(),(GLuint)(GL_TEXTURE31 - GL_TEXTURE0));
        for(GLuint texture = 0;texture < textureC;texture++)
        {
            Texture* tex = mTextures[texture];
            tex->bind(texture);
        }
        shader.use();
        bind();
        glDrawElements(GL_TRIANGLES,3 * mData.size(),GL_UNSIGNED_INT,0);
    }
    Mesh Mesh::createCube()
    {
        VertexData data = {
            // front
            {0.5f,0.5f,-0.5f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f}, // top-right
            {0.5f,-0.5f,-0.5f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f}, // bottom-right
            {-0.5f,-0.5f,-0.5f,0.0f,1.0f,1.0f,1.0f,1.0f,1.0f}, // bottom-left
            {-0.5f,0.5f,-0.5f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f}, // top-left
            // back
            {0.5f,0.5f,0.5f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f}, // top-right
            {0.5f,-0.5f,0.5f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f}, // bottom-right
            {-0.5f,-0.5f,0.5f,0.0f,1.0f,1.0f,1.0f,1.0f,1.0f}, // bottom-left
            {-0.5f,0.5f,0.5f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f}, // top-left
        };
        IndexData indices = {
            {0,4,3}, // Right
            {4,5,6},
            {0,1,3}, // Front
            {1,2,3},
            {4,5,7}, // Back
            {5,6,7}
        };

        return {data,indices};
    }
#ifdef _DEBUG
    void Mesh::Editor(Mesh& mesh,const char* name,bool* enabled)
    {
        ImGui::Begin(name,enabled);
            if(ImGui::Button("Build"))
                mesh.build();
            if(ImGui::CollapsingHeader("Vertex Data"))
            for(size_t i = 0;i < mesh.mData.size();i++)
            {
                ImGui::PushID(i);
                    VertexPayload& vertex = mesh.mData.at(i);
                    ImGui::InputFloat3("Position",vertex.p);
                    ImGui::InputFloat2("UV",vertex.tex);
                    ImGui::ColorEdit4("Color",vertex.color);
                ImGui::PopID();
            }
            if(ImGui::CollapsingHeader("Index Data"))
            for(size_t i = 0;i < mesh.mIndices.size();i++)
            {
                ImGui::PushID(i);
                std::string idx = std::to_string(i);
                if(ImGui::TreeNode(idx.c_str()))
                {
                    IndexPayload& index = mesh.mIndices.at(i);
                    ImGui::InputScalar("X",ImGuiDataType_U32,&index.x);
                    ImGui::InputScalar("Y",ImGuiDataType_U32,&index.y);
                    ImGui::InputScalar("Z",ImGuiDataType_U32,&index.z);
                    ImGui::TreePop();
                }
                ImGui::PopID();
            }
            Texture::EditorContent(mesh.mTextures);
        ImGui::End();
    }
#endif
}