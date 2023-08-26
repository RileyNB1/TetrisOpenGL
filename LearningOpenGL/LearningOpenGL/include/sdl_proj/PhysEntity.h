#pragma once

#include <vector>
#include <Collider.h>

namespace FOGrP
{
    class PhysEntity : public GameEntity
    {
    protected:
        unsigned long mId;
        std::vector<Collider*> mColliders;

        Collider* mBroadPhaseCollider;

        void AddCollider(Collider* collider, Vector2 localPos = Vec2_Zero);

        virtual bool IgnoreCollisions();

    public:
        PhysEntity();

        ~PhysEntity();

        unsigned long GetId();

        bool CheckCollision(PhysEntity* other);

        virtual void Hit(PhysEntity* other);

        virtual void Render() override;
    };

}