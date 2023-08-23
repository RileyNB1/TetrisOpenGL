#pragma once

#include <Enemy.h>

namespace Galaga
{
    class Wasp : public Enemy
    {
    private:

        static std::vector<std::vector<Vector2>> sDivePaths;
        bool mDiver;
        // Inherited via Enemy 
        Vector2 LocalFormationPosition() override;

        void HandleDiveState() override;
        void HandleDeadState() override;

        void RenderDiveState() override;
        void RenderDeadState() override;

        void FlyInComplete() override;

    public:
        static void CreateDivePaths();

        Wasp(int path, int index, bool challenge, bool diver);
        void Hit(PhysEntity* other) override;

        ~Wasp();
    };
}