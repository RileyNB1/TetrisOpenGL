#pragma once

#include <Enemy.h>

namespace Galaga
{
    class Butterfly : public Enemy
    {
    private:
        // Inherited via Enemy 
        Vector2 LocalFormationPosition() override;
        void HandleDiveState() override;
        void HandleDeadState() override;
        void RenderDiveState() override;
        void RenderDeadState() override;

        static std::vector<std::vector<Vector2>> sDivePaths;
        bool mEscort;

    public:
        Butterfly(int path, int index, bool challenge);

        ~Butterfly();

        static void CreateDivePaths();

        void Dive(int type = 0) override;
		void Hit(PhysEntity* other) override;
    };

}