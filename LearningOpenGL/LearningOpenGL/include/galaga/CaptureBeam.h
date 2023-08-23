#pragma once

#include <AnimatedTexture.h>

using namespace sdlFr;

namespace Galaga
{
    class CaptureBeam : public AnimatedTexture 
    { 
    private: 

        float mTotalCaptureTime; 
        float mCaptureTimer;

        void RunAnimation() override; 
    
    public: 
        CaptureBeam(); 
        ~CaptureBeam(); 
        
        void ResetAnimation() override; 
        void Render() override; 
    };
}