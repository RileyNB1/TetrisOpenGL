#pragma once

#include <Enemy.h>
#include <CaptureBeam.h>

namespace Galaga
{
    class Boss : public Enemy
    {
    private:
        // Inherited via Enemy 
        Vector2 LocalFormationPosition() override;

        void HandleDiveState() override;
        void HandleDeadState() override;

        void RenderDiveState() override;
        void RenderDeadState() override;

        static std::vector<std::vector<Vector2>> sDivePaths;
        bool mCaptureDive;

        int mCurrentPath;
        bool mCapturing;
        CaptureBeam* mCaptureBeam;
        bool mWasHit;

        void HandleCaptureBeam();

    public:
        Boss(int path, int index, bool challenge);
        ~Boss();
        static void CreateDivePaths();
        void Dive(int type = 0) override;
        void Hit(PhysEntity* other) override;
    };
}