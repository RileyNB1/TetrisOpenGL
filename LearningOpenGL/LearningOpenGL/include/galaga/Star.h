#pragma once
#include <Texture.h>
#include <Timer.h>
#include <Random.h>

using namespace FOGrP;

namespace Galaga
{
    class Star : public Texture
    {
    private:
        static bool mScroll;
        Timer* mTimer;
        Random* mRand;
        bool mVisible;
        float mFlickerTimer;
        float mFlickerSpeed;
        float mScrollSpeed;

        void ScrollStar();

    public:
        Star(int layer);
        ~Star();

        void Update() override;
        void Render() override;

        static void Scroll(bool b);
    };
}