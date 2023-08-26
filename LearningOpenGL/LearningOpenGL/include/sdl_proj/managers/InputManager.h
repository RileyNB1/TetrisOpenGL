#pragma once

#include <SDLMain.h>
#include <MathHelper.h>
#include <cstring>

namespace FOGrP
{
    class InputManager
    {
    private:
        static InputManager* sInstance;
        const Uint8* mKeyboardState;
        Uint8* mPrevKeyboardState;
        int mKeyLength;

        Uint32 mPrevMouseState;
        Uint32 mMouseState;
        int mMouseXPos;
        int mMouseYPos;

        InputManager();
        ~InputManager();

    public:
        enum MouseButton { Left = 0, Right, Middle, Back, Forward };
        static InputManager* Instance();
        static void Release();

        bool KeyDown(SDL_Scancode scancode);
        bool KeyPressed(SDL_Scancode scancode);
        bool KeyReleased(SDL_Scancode scancode);

        bool MouseButtonDown(MouseButton button);
        bool MouseButtonPressed(MouseButton button);
        bool MouseButtonReleased(MouseButton button);

        Vector2 MousePosition();

        void Update();
        void UpdatePrevInput();
    };
}