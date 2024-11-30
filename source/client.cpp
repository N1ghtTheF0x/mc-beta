#include "Client.hpp"
#include "Window.hpp"
#include <imgui_impl_sdl2.h>

float color[4] = {1,1,1,1};
#ifdef _DEBUG
static void imgui()
{
    ImGui::Begin("Balls");
        ImGui::ColorEdit4("diffuse",color);
    ImGui::End();
}
#endif

static SDL_Event mEvent = {0};

namespace Minecraft
{
    static OpenGL::Shader shader;
    static OpenGL::Mesh cube = OpenGL::Mesh::createCube();
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
        cube.setTexture(0,"data/icon.png");
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
        shader.set("diffuse",color[0],color[1],color[2],color[3]);
    }
    void Client::draw()
    {
        Window::beginFrame();
#ifdef _DEBUG
        imgui();
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
        Window::unload();
        SDL_Quit();
    }
}