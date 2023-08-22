#pragma once

#include <SDLTexture.h> 
#include <Timer.h> 

namespace sdlFr 
{
    enum WrapMode { Once = 0, Loop = 1 };
    enum AnimDir { Horizontal = 0, Vertical = 1 };

    class AnimatedTexture : public SDLTexture
    {
    protected: 
        Timer* mTimer; 
        int mStartX; 
        int mStartY; 
        
        int mFrameCount; // total frames 
        float mAnimationSpeed; // in seconds 
        float mTimePerFrame; // time to display 
        float mAnimationTimer; // time displayed

        WrapMode mWrapMode; 
        AnimDir mAnimationDirection; 
        bool mAnimationDone;

        virtual void RunAnimation();

    public:
        AnimatedTexture(std::string filename, 
            int x, int y, int w, int h, 
            int frameCount, 
            float animationSpeed, 
            AnimDir animationDir, bool managed = false);
        
        virtual ~AnimatedTexture();

        void SetWrapMode(WrapMode mode); 
        virtual void ResetAnimation(); 
        bool IsAnimating(); 
        void Update();
    };
}