#include "Shader.hpp"
#include "../fs/File.hpp"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifdef _DEBUG
    #include <imgui.h>
#endif

namespace Minecraft::OpenGL
{
    static GLuint create_shader(const char* code,GLenum type)
    {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader,1,&code,0);
        glCompileShader(shader);
        GLint result;
        glGetShaderiv(shader,GL_COMPILE_STATUS,&result);
        if(!result)
        {
            GLint size;
            glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&size);
            std::string info(size,' ');
            glGetShaderInfoLog(shader,size,0,info.data());
            std::cerr << info << std::endl;
        }
        return shader;
    }
    static GLuint create_program(GLuint vertex,GLuint fragment)
    {
        GLuint program = glCreateProgram();
        glAttachShader(program,vertex);
        glAttachShader(program,fragment);
        glLinkProgram(program);
        GLint result;
        glGetProgramiv(program,GL_LINK_STATUS,&result);
        if(!result)
        {
            GLint size;
            glGetProgramiv(program,GL_INFO_LOG_LENGTH,&size);
            std::string info(size,' ');
            glGetProgramInfoLog(program,size,0,info.data());
            std::cerr << info << std::endl;
        }
        return program;
    }
    Shader::~Shader()
    {
        glDeleteProgram(mProgram);
    }
    void Shader::reload()
    {
        std::string vertex = FileSystem::readFile(DEFAULT_VERTEX);
        std::string fragment = FileSystem::readFile(DEFAULT_FRAGMENT);
        reload(vertex.c_str(),fragment.c_str());
    }
    void Shader::reload(GLuint vertex,GLuint fragment)
    {
        glDeleteProgram(mProgram);
        mProgram = create_program(vertex,fragment);
        use();
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    void Shader::reload(const char* vertex,const char* fragment)
    {
        reload(create_shader(vertex,GL_VERTEX_SHADER),create_shader(fragment,GL_FRAGMENT_SHADER));
    }
    void Shader::use() const
    {
        glUseProgram(mProgram);
    }
    void Shader::set(std::string uniform,GLfloat x,GLfloat y,GLfloat z,GLfloat w)
    {
        use();
        glUniform4f(glGetUniformLocation(mProgram,uniform.c_str()),x,y,z,w);
    }
    void Shader::set(std::string uniform,Math::Color color)
    {
        set(uniform,color.red,color.green,color.blue,color.alpha);
    }
    void Shader::set(std::string uniform,GLfloat x,GLfloat y,GLfloat z)
    {
        use();
        glUniform3f(glGetUniformLocation(mProgram,uniform.c_str()),x,y,z);
    }
    void Shader::set(std::string uniform,glm::vec3 vec)
    {
        set(uniform,vec.x,vec.y,vec.z);
    }
    void Shader::set(std::string uniform,GLfloat x,GLfloat y)
    {
        use();
        glUniform2f(glGetUniformLocation(mProgram,uniform.c_str()),x,y);
    }
    void Shader::set(std::string uniform,glm::vec2 vec)
    {
        set(uniform,vec.x,vec.y);
    }
    void Shader::set(std::string uniform,GLfloat x)
    {
        use();
        glUniform1f(glGetUniformLocation(mProgram,uniform.c_str()),x);
    }
    void Shader::set(std::string uniform,GLint x)
    {
        use();
        glUniform1i(glGetUniformLocation(mProgram,uniform.c_str()),x);
    }
    void Shader::set(std::string uniform,glm::mat3 mat)
    {
        use();
        glUniformMatrix3fv(glGetUniformLocation(mProgram,uniform.c_str()),1,false,glm::value_ptr(mat));
    }
    void Shader::set(std::string uniform,glm::mat4 mat)
    {
        use();
        glUniformMatrix4fv(glGetUniformLocation(mProgram,uniform.c_str()),1,false,glm::value_ptr(mat));
    }
    void Shader::getFloat(std::string uniform,GLfloat* ptr) const
    {
        use();
        glGetUniformfv(mProgram,glGetUniformLocation(mProgram,uniform.c_str()),ptr);
    }
    void Shader::getInt(std::string uniform,GLint* ptr) const
    {
        use();
        glGetUniformiv(mProgram,glGetUniformLocation(mProgram,uniform.c_str()),ptr);
    }
    void Shader::getInt(std::string uniform,GLuint* ptr) const
    {
        use();
        glGetUniformuiv(mProgram,glGetUniformLocation(mProgram,uniform.c_str()),ptr);
    }
    glm::vec2 Shader::getVector2(std::string uniform) const
    {
        float v[2];
        getFloat(uniform,v);
        return {v[0],v[1]};
    }
    glm::vec3 Shader::getVector3(std::string uniform) const
    {
        float v[3];
        getFloat(uniform,v);
        return {v[0],v[1],v[2]};
    }
    glm::mat3 Shader::getMat3(std::string uniform) const
    {
        float v[9];
        getFloat(uniform,v);
        return glm::mat3(
            v[0],v[1],v[2],
            v[3],v[4],v[5],
            v[6],v[7],v[8]
        );
    }
    glm::mat4 Shader::getMat4(std::string uniform) const
    {
        float v[16];
        getFloat(uniform,v);
        return glm::mat4(
            v[0],v[1],v[2],v[3],
            v[4],v[5],v[6],v[7],
            v[8],v[9],v[10],v[11],
            v[12],v[13],v[14],v[15]
        );
    }
    Math::Color Shader::getColor(std::string uniform) const
    {
        Math::Color vec;
        getFloat(uniform,vec.data);
        return vec;
    }
#ifdef _DEBUG
    void Shader::Editor(Shader& shader,const char* name,bool* enabled)
    {
        ImGui::Begin(name,enabled);
            GLint uniformC, uniformL;
            glGetProgramiv(shader.mProgram,GL_ACTIVE_UNIFORMS,&uniformC);
            glGetProgramiv(shader.mProgram,GL_ACTIVE_UNIFORM_MAX_LENGTH,&uniformL);
            for(GLint i = 0;i < uniformC;i++)
            {
                std::string name(uniformL,' ');
                GLenum type;
                GLsizei length;
                GLint size;
                glGetActiveUniform(shader.mProgram,i,uniformL,&length,&size,&type,name.data());
                switch(type)
                {
                    case GL_FLOAT:
                    {
                        float value;
                        shader.getFloat(name,&value);
                        if(ImGui::CollapsingHeader(name.c_str()))
                        {
                            ImGui::InputFloat("Value",&value);
                        }
                        shader.set(name,value);
                        break;
                    }
                    case GL_FLOAT_VEC2:
                    {
                        float value[2];
                        shader.getFloat(name,value);
                        if(ImGui::CollapsingHeader(name.c_str()))
                        {
                            ImGui::InputFloat2("Value",value);
                        }
                        shader.set(name,value[0],value[1]);
                        break;
                    }
                    case GL_FLOAT_VEC3:
                    {
                        float value[3];
                        shader.getFloat(name,value);
                        if(ImGui::CollapsingHeader(name.c_str()))
                        {
                            ImGui::InputFloat3("Value",value);
                            ImGui::ColorEdit3("Color",value);
                        }
                        shader.set(name,value[0],value[1],value[2]);
                        break;
                    }
                    case GL_FLOAT_VEC4:
                    {
                        float value[4];
                        shader.getFloat(name,value);
                        if(ImGui::CollapsingHeader(name.c_str()))
                        {
                            ImGui::InputFloat4("Value",value);
                            ImGui::ColorEdit4("Color",value);
                        }
                        shader.set(name,value[0],value[1],value[2],value[3]);
                        break;
                    }
                    case GL_SAMPLER_2D:
                    {
                        GLint texture;
                        shader.getInt(name,&texture);
                        if(ImGui::CollapsingHeader(name.c_str()))
                            ImGui::InputInt("Value",&texture);
                        shader.set(name,texture);
                        break;
                    }
                    case GL_FLOAT_MAT3:
                    {
                        glm::mat3 mat = shader.getMat3(name);
                        glm::f32* ptr = glm::value_ptr(mat);
                        if(ImGui::CollapsingHeader(name.c_str()))
                        {
                            ImGui::InputFloat3("Row 1",ptr);
                            ImGui::InputFloat3("Row 2",ptr + 3);
                            ImGui::InputFloat3("Row 3",ptr + 6);
                        }
                        shader.set(name,mat);
                        break;
                    }
                    case GL_FLOAT_MAT4:
                    {
                        glm::mat4 mat = shader.getMat4(name);
                        glm::f32* ptr = glm::value_ptr(mat);
                        if(ImGui::CollapsingHeader(name.c_str()))
                        {
                            ImGui::InputFloat4("Row 1",ptr);
                            ImGui::InputFloat4("Row 2",ptr + 4);
                            ImGui::InputFloat4("Row 3",ptr + 8);
                            ImGui::InputFloat4("Row 4",ptr + 12);
                        }
                        shader.set(name,mat);
                        break;
                    }
                    default:
                        ImGui::Text("unknown uniform '%s'",name.c_str());
                        break;
                }
            }
        ImGui::End();
    }
#endif
}