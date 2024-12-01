#include "Window.hpp"
#include <iostream>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <MinecraftConfig.hpp>

namespace Minecraft
{
    static SDL_Window* mWindow = nullptr;
    static SDL_GLContext mGL = nullptr;
    void Window::unload()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
        if(mGL != nullptr)
            SDL_GL_DeleteContext(mGL);
        if(mWindow != nullptr)
            SDL_DestroyWindow(mWindow);
    }
    void Window::load()
    {
        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
        {
            std::cerr << "Failed to load SDL: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    void Window::create()
    {
        int context_flags = SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG;
#ifdef _DEBUG
        context_flags |= SDL_GL_CONTEXT_DEBUG_FLAG;
#endif
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,context_flags);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,2);
        mWindow = SDL_CreateWindow(
            MINECRAFT_TITLE,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
        );
        if(mWindow == nullptr)
        {
            std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        mGL = SDL_GL_CreateContext(mWindow);
        if(mGL == nullptr)
        {
            std::cerr << "Failed to create OpenGL Context: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        SDL_GL_MakeCurrent(mWindow,mGL);
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplSDL2_InitForOpenGL(mWindow,mGL);
        if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            std::cerr << "Failed to load GLAD" << std::endl;
            exit(EXIT_FAILURE);
        }
        ImGui_ImplOpenGL3_Init();
        glEnable(GL_DEPTH_TEST);
    }
    SDL_Window* Window::sdlWindow()
    {
        return mWindow;
    }
    SDL_GLContext Window::sdlGLContext()
    {
        return mGL;
    }
    void Window::beginFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }
    void Window::endFrame()
    {
        ImGui::Render();
        swap();
    }
    void Window::clear()
    {
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void Window::swap()
    {
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(mWindow);
    }
    void Window::vsync(bool state)
    {
        SDL_GL_SetSwapInterval(state ? 1 : 0);
    }
    void Window::size(int* width,int* height)
    {
        SDL_GetWindowSize(mWindow,width,height);
    }
}