#ifndef __MINECRAFT_INPUT_HPP
#define __MINECRAFT_INPUT_HPP

#include <SDL.h>

namespace Minecraft
{
    class InputManager
    {
    private:
        Uint8 mLastFrame[SDL_NUM_SCANCODES];
        Uint8 mCurrentFrame[SDL_NUM_SCANCODES];
    public:
        void update();
        bool isPressed(SDL_Scancode scan) const;
        bool isJustPressed(SDL_Scancode scan) const;
        bool isReleased(SDL_Scancode scan) const;
    };
}

#endif