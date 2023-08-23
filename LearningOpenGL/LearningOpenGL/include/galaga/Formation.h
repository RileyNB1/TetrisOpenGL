#pragma once

#include <GameEntity.h>
#include <Timer.h>

using namespace sdlFr;

namespace Galaga
{
    class Formation : public GameEntity
    {
    private:
        Timer* mTimer;
        // side-to-side movement while still spawning 
        float mOffsetAmount;
        float mOffsetTimer;
        float mOffsetDelay;
        int mOffsetCounter;
        int mOffsetDirection;

        // breathing animation when formation locked 
        float mSpreadTimer;
        float mSpreadDelay;
        int mSpreadCounter;
        int mSpreadDirection;

        Vector2 mGridSize; //in pixels 
        bool mLocked;

    public:
        Formation();
        ~Formation();

        Vector2 GridSize();
        int GetTick();
        void Lock();
        bool Locked();

        void Update() override;
    };
}