#include "Input.hpp"
#include <memory>

namespace Minecraft
{
    void InputManager::update()
    {
        std::memcpy(mLastFrame,mCurrentFrame,SDL_NUM_SCANCODES * sizeof(Uint8));
        int keys;
        const Uint8* state = SDL_GetKeyboardState(&keys);
        std::memcpy(mCurrentFrame,state,keys);
    }
    bool InputManager::isPressed(SDL_Scancode scan) const
    {
        return mCurrentFrame[scan] && mLastFrame[scan];
    }
    bool InputManager::isJustPressed(SDL_Scancode scan) const
    {
        return mCurrentFrame[scan] && !mLastFrame[scan];
    }
    bool InputManager::isReleased(SDL_Scancode scan) const
    {
        return mCurrentFrame[scan] && mLastFrame[scan];
    }
}