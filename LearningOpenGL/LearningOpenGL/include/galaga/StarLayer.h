#pragma once

#include <Star.h>

namespace Galaga
{

    class StarLayer
    {
    private:

        static const int STAR_COUNT = 30;
        Star* mStars[STAR_COUNT];

    public:
        StarLayer(int layer);
        ~StarLayer();
        void Update();
        void Render();
    };
}