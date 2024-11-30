#ifndef __MINECRAFT_OPENGL_SHADER_HPP
#define __MINECRAFT_OPENGL_SHADER_HPP

#include <glad/glad.h>

namespace Minecraft::OpenGL
{
    #define DEFAULT_VERTEX "data/shaders/vertex.glsl"
    #define DEFAULT_FRAGMENT "data/shaders/fragment.glsl"
    class Shader
    {
    private:
        GLuint mProgram;
    public:
        ~Shader();
        operator GLuint() const {return mProgram;}

        void reload();
        void reload(GLuint vertex,GLuint fragment);
        void reload(const char* vertex,const char* fragment);
        void use() const;
        void set(const char* uniform,float x,float y,float z,float w);
        void set(const char* uniform,float x,float y,float z);
        void set(const char* uniform,float x,float y);
        void set(const char* uniform,int x);
    };
#ifdef _DEBUG
    void ImGuiEditor(Shader& shaderm,const char* name,bool* enabled);
#endif
}

#endif