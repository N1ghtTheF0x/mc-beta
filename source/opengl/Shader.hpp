#ifndef __MINECRAFT_OPENGL_SHADER_HPP
#define __MINECRAFT_OPENGL_SHADER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

#include "../math/Color.hpp"

namespace Minecraft::OpenGL
{
    #define DEFAULT_VERTEX "data/shaders/vertex.glsl"
    #define DEFAULT_FRAGMENT "data/shaders/fragment.glsl"
    class Shader
    {
    private:
        GLuint mProgram;
    public:
#ifdef _DEBUG
        static void Editor(Shader& shader,const char* name,bool* enabled = (bool*)0);
#endif
        ~Shader();

        void reload();
        void reload(GLuint vertex,GLuint fragment);
        void reload(const char* vertex,const char* fragment);
        void use() const;
        void set(std::string uniform,GLfloat x,GLfloat y,GLfloat z,GLfloat w);
        void set(std::string uniform,Math::Color color);
        void set(std::string uniform,glm::vec4 vec);
        void set(std::string uniform,GLfloat x,GLfloat y,GLfloat z);
        void set(std::string uniform,glm::vec3 vec);
        void set(std::string uniform,GLfloat x,GLfloat y);
        void set(std::string uniform,glm::vec2 vec);
        void set(std::string uniform,GLfloat x);
        void set(std::string uniform,GLint x);
        void set(std::string uniform,glm::mat3 mat);
        void set(std::string uniform,glm::mat4 mat);
        void getFloat(std::string uniform,GLfloat* ptr) const;
        void getInt(std::string uniform,GLint* ptr) const;
        void getInt(std::string uniform,GLuint* ptr) const;
        glm::vec2 getVector2(std::string uniform) const;
        glm::vec3 getVector3(std::string uniform) const;
        glm::vec4 getVector4(std::string uniform) const;
        glm::mat3 getMat3(std::string uniform) const;
        glm::mat4 getMat4(std::string uniform) const;
        Math::Color getColor(std::string uniform) const;
    };
}

#endif