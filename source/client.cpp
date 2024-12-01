#include "Client.hpp"
#include "Window.hpp"
#include "fs/File.hpp"
#include "math/Camera.hpp"
#include <imgui_impl_sdl2.h>
#include <glm/gtc/matrix_transform.hpp>

static SDL_Event mEvent = {0};

namespace Minecraft
{
    static OpenGL::Shader shader;
    static OpenGL::Mesh cube = OpenGL::Mesh::createCube();
    static OpenGL::Texture grass = FileSystem::readTexture("data/icon.png");
    static glm::mat4 model(1.0f);
    static Math::Camera camera(0,0,3);
    static float moveSpeed = 2.5f;
    static float lookSpeed = 100.0f;
    static float yaw = 0.0f;
    static float pitch = 0.0f;
    static glm::mat4 projection;
    static Uint64 mCurrentFrame = 0;
    static Uint64 mLastFrame = 0;
#ifdef _DEBUG
    static void imgui()
    {
        ImGui::Begin("Camera Settings");
            ImGui::InputFloat("Move Speed",&moveSpeed);
            ImGui::InputFloat("Look Speed",&lookSpeed);
        ImGui::End();
    }
#endif
    Client::Client(int argc,char* argv[]): Instance(argc,argv)
    {
        Window::load();
    }
    Client::~Client()
    {
        
    }
    void Client::init()
    {
        Window::create();
        shader.reload();
        cube.load();
        cube.build();
        cube.addTexture(&grass);
        shader.set("diffuseT",0);
        model = glm::rotate(model,glm::radians(25.0f),{1.0f,0.0f,0.0f});
        loop();
    }
    void Client::loop()
    {
        while(mRunning)
        {
            event();
            update();
            draw();
        }
        cleanup();
    }
    void Client::event()
    {
        while(SDL_PollEvent(&mEvent))
        {
#ifdef _DEBUG
            ImGui_ImplSDL2_ProcessEvent(&mEvent);
#endif
            switch(mEvent.type)
            {
                case SDL_QUIT:
                    mRunning = false;
                    break;
                case SDL_KEYDOWN:
                    SDL_Scancode scan = mEvent.key.keysym.scancode;
                    if(scan == SDL_SCANCODE_W)
                        camera.moveForward(moveSpeed * mDeltaTime);
                    if(scan == SDL_SCANCODE_S)
                        camera.moveBackwards(moveSpeed * mDeltaTime);
                    if(scan == SDL_SCANCODE_A)
                        camera.moveLeft(moveSpeed * mDeltaTime);
                    if(scan == SDL_SCANCODE_D)
                        camera.moveRight(moveSpeed * mDeltaTime);
                    if(scan == SDL_SCANCODE_SPACE)
                        camera.moveUp(moveSpeed * mDeltaTime);
                    if(scan == SDL_SCANCODE_LSHIFT)
                        camera.moveDown(moveSpeed * mDeltaTime);
                    if(scan == SDL_SCANCODE_LEFT)
                        yaw -= lookSpeed * mDeltaTime;
                    if(scan == SDL_SCANCODE_RIGHT)
                        yaw += lookSpeed * mDeltaTime;
                    if(scan == SDL_SCANCODE_UP)
                        pitch += lookSpeed * mDeltaTime;
                    if(scan == SDL_SCANCODE_DOWN)
                        pitch -= lookSpeed * mDeltaTime;
                    break;
            }
        }
    }
    void Client::update()
    {
        mLastFrame = mCurrentFrame;
        mCurrentFrame = SDL_GetTicks64();
        mDeltaTime = (float)(mCurrentFrame-mLastFrame)/1000.0f;

        int width, height;
        Window::size(&width,&height);
        projection = glm::perspective(glm::radians(45.0f),(float)width/(float)height,0.1f,100.0f);
        camera.look(yaw,std::clamp(pitch,-89.0f,89.0f),0);
        shader.set("model",model);
        shader.set("view",camera.view());
        shader.set("projection",projection);
    }
    void Client::draw()
    {
        Window::beginFrame();
#ifdef _DEBUG
        imgui();
        Math::Camera::Editor(camera,"Camera");
        OpenGL::Mesh::Editor(cube,"Cube");
        OpenGL::Shader::Editor(shader,"Shader");
#endif
        Window::clear();
        int width, height;
        Window::size(&width,&height);
        glViewport(0,0,width,height);
        // draw calls go here
        cube.draw(shader);
        Window::endFrame();
    }
    void Client::cleanup()
    {
        cube.unload();
        grass.unload();
        Window::unload();
        SDL_Quit();
    }
}