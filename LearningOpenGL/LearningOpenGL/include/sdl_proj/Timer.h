#pragma once

#include <SDLMain.h> 

namespace FOGrP
{
    class Timer
    {
    private:
        static Timer* sInstance;
        unsigned int mStartTicks;
        unsigned int mElapsedTicks;
        float mDeltaTime;
        float mTimeScale;

        Timer();
        ~Timer();

    public:
        static Timer* Instance();
        static void Release();
        void Reset();
        float DeltaTime() const;
        void TimeScale(float ts);
        float TimeScale() const;
        void Update();
    };
}