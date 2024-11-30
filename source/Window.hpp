#ifndef __MINECRAFT_WINDOW_HPP
#define __MINECRAFT_WINDOW_HPP

#include <SDL.h>
#include "opengl/OpenGL.hpp"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

namespace Minecraft
{
    namespace Window
    {
        void unload();
        void load();
        void create();
        
        SDL_Window* sdlWindow();
        SDL_GLContext sdlGLContext();

        void beginFrame();
        void endFrame();
        void clear();
        void swap();
        void vsync(bool state);
        void size(int* width,int* height);
    }
};

#endif