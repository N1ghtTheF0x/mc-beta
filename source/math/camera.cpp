#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef _DEBUG
    #include <imgui.h>
#endif

namespace Minecraft::Math
{
    const glm::vec3 Camera::FRONT = {0,0,-1};
    const glm::vec3 Camera::UP = {0,1,0};
    Camera::Camera(): mPosition(0,0,0), mFront(FRONT), mUp(UP)
    {

    }
    Camera::Camera(glm::vec3 position): mPosition(position), mFront(FRONT), mUp(UP)
    {

    }
    Camera::Camera(float x,float y,float z): mPosition(x,y,z), mFront(FRONT), mUp(UP)
    {

    }
    glm::vec3 Camera::position() const
    {
        return mPosition;
    }
    void Camera::setPosition(glm::vec3 position)
    {
        mPosition = position;
    }
    void Camera::setPosition(float x,float y,float z)
    {
        mPosition = {x,y,z};
    }
    void Camera::look(glm::vec3 look)
    {
        this->look(look.x,look.y,look.z);
    }
    void Camera::look(float yaw,float pitch,float roll)
    {
        mFront = glm::normalize(glm::vec3(
            std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch)),
            std::sin(glm::radians(pitch)),
            std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch))
        ));
    }
    void Camera::lookLeft(float speed)
    {
        look(speed,0,0);
    }
    void Camera::lookRight(float speed)
    {
        look(-speed,0,0);
    }
    void Camera::lookUp(float speed)
    {
        look(0,speed,0);
    }
    void Camera::lookDown(float speed)
    {
        look(0,-speed,0);
    }
    glm::mat4 Camera::view() const
    {
        return glm::lookAt(
            mPosition,
            mPosition + mFront,
            mUp
        );
    }
    void Camera::moveForward(float speed)
    {
        mPosition += speed * mFront;
    }
    void Camera::moveBackwards(float speed)
    {
        mPosition -= speed * mFront;
    }
    void Camera::moveLeft(float speed)
    {
        mPosition -= glm::normalize(glm::cross(mFront,mUp)) * speed;
    }
    void Camera::moveRight(float speed)
    {
        mPosition += glm::normalize(glm::cross(mFront,mUp)) * speed;
    }
    void Camera::moveUp(float speed)
    {
        mPosition += glm::vec3(0,speed,0);
    }
    void Camera::moveDown(float speed)
    {
        mPosition -= glm::vec3(0,speed,0);
    }
#ifdef _DEBUG
    void Camera::Editor(Camera& camera,const char* name,bool* enabled)
    {
        ImGui::Begin(name,enabled);
            glm::f32* position = glm::value_ptr(camera.mPosition);
            ImGui::InputFloat3("Position",position);
        ImGui::End();
    }
#endif
}