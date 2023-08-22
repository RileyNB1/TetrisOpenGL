#pragma once

#include <bitset>
#include <vector>
#include <CircleCollider.h>
#include <PhysicsHelper.h>
#include <GameEntity.h>
#include <PhysEntity.h>

namespace sdlFr
{
    class PhysicsManager
    {
    public:
        static PhysicsManager* Instance();

        static void Release();

        enum class CollisionLayers
        {
            Friendly,
            FriendlyProjectiles,
            Hostile,
            HostileProjectiles,
            MaxLayers
        };

        enum class CollisionFlags
        {
            None = 0x00,
            Friendly = 0x01,
            FriendlyProjectiles = 0x02,
            Hostile = 0x04,
            HostileProjectiles = 0x08
        };

        void SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags);

        unsigned long RegisterEntity(PhysEntity* entity, CollisionLayers layer);

        void UnregisterEntity(unsigned long id);

        void Update();
    private:
        static PhysicsManager* sInstance;

        PhysicsManager();

        ~PhysicsManager();

        std::vector<PhysEntity*> mCollisionLayers[static_cast<unsigned int>(CollisionLayers::MaxLayers)];

        std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)>
            mLayerMasks[static_cast<unsigned int>(CollisionLayers::MaxLayers)];

        unsigned long mLastId;
    };

    inline PhysicsManager::CollisionFlags operator|(
        PhysicsManager::CollisionFlags a,
        PhysicsManager::CollisionFlags b)
    {
        return static_cast<PhysicsManager::CollisionFlags>
            (
                static_cast<unsigned int>(a)
                | static_cast<unsigned int>(b));
    }

    inline PhysicsManager::CollisionFlags operator&(
        PhysicsManager::CollisionFlags a,
        PhysicsManager::CollisionFlags b)
    {
        return static_cast<PhysicsManager::CollisionFlags>
            (
                static_cast<unsigned int>(a)
                & static_cast<unsigned int>(b));
    }
}