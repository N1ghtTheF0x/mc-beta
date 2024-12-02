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
    float Camera::yaw() const
    {
        return mYaw;
    }
    float Camera::pitch() const
    {
        return mPitch;
    }
    void Camera::setPosition(glm::vec3 position)
    {
        mPosition = position;
    }
    void Camera::setPosition(float x,float y,float z)
    {
        mPosition = {x,y,z};
    }
    void Camera::setYaw(float yaw)
    {
        mYaw = yaw;
    }
    void Camera::setPitch(float pitch)
    {
        mPitch = pitch;
    }
    void Camera::update()
    {
        mFront = glm::normalize(glm::vec3(
            std::cos(glm::radians(mYaw)) * std::cos(glm::radians(mPitch)),
            std::sin(glm::radians(mPitch)),
            std::sin(glm::radians(mYaw)) * std::cos(glm::radians(mPitch))
        ));
    }
    void Camera::lookLeft(float speed)
    {
        mYaw -= speed;
    }
    void Camera::lookRight(float speed)
    {
        mYaw += speed;
    }
    void Camera::lookUp(float speed)
    {
        mPitch += speed;
    }
    void Camera::lookDown(float speed)
    {
        mPitch -= speed;
    }
    glm::mat4 Camera::view() const
    {
        return glm::lookAt(
            mPosition,
            mPosition + mFront,
            mUp
        );
    }
    void Camera::moveTowards(float speed)
    {
        mPosition += speed * mFront;
    }
    void Camera::moveForward(float speed)
    {
        
    }
    void Camera::moveBackwards(float speed)
    {
        
    }
    void Camera::moveAway(float speed)
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
            glm::f32* front = glm::value_ptr(camera.mFront);
            ImGui::InputFloat3("Position",position);
            ImGui::InputFloat3("Front",front);
            ImGui::InputFloat("Yaw",&camera.mYaw);
            ImGui::InputFloat("Pitch",&camera.mPitch);
        ImGui::End();
    }
#endif
}