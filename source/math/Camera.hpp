#ifndef __MINECRAFT_MATH_CAMERA_HPP
#define __MINECRAFT_MATH_CAMERA_HPP

#include <glm/glm.hpp>

namespace Minecraft::Math
{
    class Camera
    {
    private:
        glm::vec3 mPosition;
        glm::vec3 mFront;
        glm::vec3 mUp;
        float mSpeedXY;
    public:
        static const glm::vec3 FRONT;
        static const glm::vec3 UP;
#ifdef _DEBUG
        static void Editor(Camera& camera,const char* name,bool* enabled = (bool*)0);
#endif
        Camera();
        Camera(glm::vec3 position);
        Camera(float x,float y,float z);
        glm::vec3 position() const;
        void setPosition(glm::vec3 move);
        void setPosition(float x,float y,float z);
        void look(glm::vec3 look);
        void look(float yaw,float pitch,float roll);
        void lookUp(float speed);
        void lookDown(float speed);
        void lookLeft(float speed);
        void lookRight(float speed);
        glm::mat4 view() const;
        void moveLeft(float speed);
        void moveRight(float speed);
        void moveForward(float speed);
        void moveBackwards(float speed);
        void moveUp(float speed);
        void moveDown(float speed);
    };
}

#endif