#pragma once

#include <PhysEntity.h>
#include <Timer.h>
#include <Texture.h>
#include <managers/PhysicsManager.h>

using namespace sdlFr;

namespace Galaga
{
    class Bullet : public PhysEntity
    {
    private:
        static const int OFFSCREEN_BUFFER = 10;
        Timer* mTimer;
        Texture* mTexture;
        float mSpeed;

        bool IgnoreCollisions() override;

    public:
        Bullet(bool friendly);
        ~Bullet();

        void Fire(Vector2 pos);
        void Reload();

        void Update() override;
        void Render() override;
        void Hit(PhysEntity* other) override;
    };

}