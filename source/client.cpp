#include "Client.hpp"
#include "Window.hpp"
#include "math/Camera.hpp"

#include <chrono>
#include <imgui_impl_sdl2.h>
#include <glm/gtc/matrix_transform.hpp>

static SDL_Event mEvent = {0};

using Clock = std::chrono::system_clock;
using DeltaTime = std::chrono::duration<float>;

namespace Minecraft
{
    static OpenGL::Shader shader;
    static glm::mat4 model(1.0f);
    static Math::Camera camera(-3,1,0);
    static float moveSpeed = 2.5f;
    static float lookSpeed = 100.0f;
    static glm::mat4 projection;
    static Clock::time_point mCurrentFrame;
    static Clock::time_point mLastFrame;
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
        auto cube = mAssets.addMesh({"minecraft","block"},OpenGL::Mesh::createCube());
        cube->load();
        cube->addTexture(mAssets.addTexture({"minecraft","grass_side"},"data/icon.png"));
        shader.set("diffuseT",0);
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
            }
        }
    }
    void Client::update()
    {
        mLastFrame = mCurrentFrame;
        mCurrentFrame = Clock::now();
        auto deltaTime = mCurrentFrame - mLastFrame;
        mDeltaTime = std::chrono::duration_cast<DeltaTime>(deltaTime).count();
        mInput.update();
        if(mInput.isPressed(SDL_SCANCODE_W))
            camera.moveTowards(moveSpeed * mDeltaTime);
        if(mInput.isPressed(SDL_SCANCODE_S))
            camera.moveAway(moveSpeed * mDeltaTime);
        if(mInput.isPressed(SDL_SCANCODE_A))
            camera.moveLeft(moveSpeed * mDeltaTime);
        if(mInput.isPressed(SDL_SCANCODE_D))
            camera.moveRight(moveSpeed * mDeltaTime);
        if(mInput.isPressed(SDL_SCANCODE_SPACE))
            camera.moveUp(moveSpeed * mDeltaTime);
        if(mInput.isPressed(SDL_SCANCODE_LSHIFT))
            camera.moveDown(moveSpeed * mDeltaTime);
        if(mInput.isPressed(SDL_SCANCODE_LEFT))
            camera.lookLeft(lookSpeed * mDeltaTime);
        if(mInput.isPressed(SDL_SCANCODE_RIGHT))
            camera.lookRight(lookSpeed * mDeltaTime);
        if(mInput.isPressed(SDL_SCANCODE_UP))
            camera.lookUp(lookSpeed * mDeltaTime);
        if(mInput.isPressed(SDL_SCANCODE_DOWN))
            camera.lookDown(lookSpeed * mDeltaTime);
        camera.update();
        int width, height;
        Window::size(&width,&height);
        projection = glm::perspective(glm::radians(45.0f),(float)width/(float)height,0.1f,100.0f);
        shader.set("model",model);
        shader.set("view",camera.view());
        shader.set("projection",projection);
    }
    void Client::draw()
    {
        Window::beginFrame();
#ifdef _DEBUG
        ImGui::Begin("Scene Settings");
            ImGui::Text("Delta Time: %f",mDeltaTime);
            ImGui::Text("FPS: %i",(int)(1.0f/mDeltaTime));
            ImGui::InputFloat("Move Speed",&moveSpeed);
            ImGui::InputFloat("Look Speed",&lookSpeed);
        ImGui::End();
        Math::Camera::Editor(camera,"Camera");
        AssetManager::Editor(mAssets,"Assets");
        OpenGL::Shader::Editor(shader,"Shader");
#endif
        Window::clear();
        int width, height;
        Window::size(&width,&height);
        glViewport(0,0,width,height);
        // draw calls go here
        auto& cube = mAssets.getMesh("minecraft:block");
        cube->draw(shader);
        Window::endFrame();
    }
    void Client::cleanup()
    {
        mAssets.unload();
        Window::unload();
        SDL_Quit();
    }
}