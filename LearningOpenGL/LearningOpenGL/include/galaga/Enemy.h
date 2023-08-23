#pragma once

#include <vector>
#include <Formation.h>
#include <PhysEntity.h>
#include <MathHelper.h>
#include <Player.h>
#include <Timer.h>
#include <BezierPath.h>

using namespace sdlFr;

typedef Galaga::Formation Swarm;

namespace Galaga
{
    class Enemy : public PhysEntity
    {
    public:
        enum States { FlyIn, Formation, Diving, Dead };
        enum Types { Butterfly, Wasp, Boss };

        static void SetFormation(Swarm* formation);
        bool InDeathAnimation();

    protected:

        static Player* sPlayer;

        static std::vector<std::vector<Vector2>> sPaths;
        static Swarm* sFormation;

        Timer* mTimer;
        
        Texture* mTexture;
        Texture* mTextures[2];

        States mCurrentState;
        unsigned mCurrentPath;
        unsigned mCurrentWaypoint;

        int mIndex;
        Types mType;
        bool mChallengeStage;
        Vector2 mDiveStartPosition; 
        
        AnimatedTexture* mDeathAnimation;

        const float EPSILON = 5.0f;
        float mSpeed;

        virtual void HandleFlyInState();
        virtual void HandleFormationState();

        void HandleStates();

        virtual void RenderFlyInState();
        virtual void RenderFormationState();

        virtual void PathComplete();
        virtual void FlyInComplete();
        void JoinFormation();
        virtual Vector2 WorldFormationPosition();

        virtual Vector2 LocalFormationPosition() = 0;
        virtual void HandleDiveState() = 0;
        virtual void HandleDeadState() = 0;
        virtual void RenderDiveState() = 0;
        virtual void RenderDeadState() = 0;

        void RenderStates();

        bool IgnoreCollisions() override;

    public:
        static void CreatePaths();
        Enemy(int path, int index, bool challenge);

        virtual ~Enemy();
        States CurrentState();

        void Update() override;
        void Render() override;

        Types Type();
        int Index();

        virtual void Dive(int type = 0);

        static void CurrentPlayer(Player* player);

        virtual void Hit(PhysEntity* other) override;
    };
}