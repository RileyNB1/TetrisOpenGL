#pragma once

#include <StartScreen.h>
#include <PlayScreen.h>
#include <BackgroundStars.h>

namespace Galaga
{
    class ScreenManager
    {
    private:
        static ScreenManager* sInstance;
        ScreenManager(); ~ScreenManager();

        enum Screens { Start, Play };
        Screens mCurrentScreen;

        InputManager* mInput;
        BackgroundStars* mBackgroundStars;

        StartScreen* mStartScreen;
        PlayScreen* mPlayScreen;

    public:
        static ScreenManager* Instance();
        static void Release();

        void Update();
        void Render();
    };
}