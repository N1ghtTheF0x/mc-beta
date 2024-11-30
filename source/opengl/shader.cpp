#include "Shader.hpp"
#include "../fs/File.hpp"
#include <iostream>

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
    void Shader::set(const char* uniform,float x,float y,float z,float w)
    {
        use();
        glUniform4f(glGetUniformLocation(mProgram,uniform),x,y,z,w);
    }
    void Shader::set(const char* uniform,float x,float y,float z)
    {
        use();
        glUniform3f(glGetUniformLocation(mProgram,uniform),x,y,z);
    }
    void Shader::set(const char* uniform,float x,float y)
    {
        use();
        glUniform2f(glGetUniformLocation(mProgram,uniform),x,y);
    }
    void Shader::set(const char* uniform,int x)
    {
        use();
        glUniform1i(glGetUniformLocation(mProgram,uniform),x);
    }
#ifdef _DEBUG
    void ImGuiEditor(Shader& shader,const char* name,bool* enabled)
    {
        float vec[4];
        ImGui::Begin(name,enabled);
            
        ImGui::End();
    }
#endif
}