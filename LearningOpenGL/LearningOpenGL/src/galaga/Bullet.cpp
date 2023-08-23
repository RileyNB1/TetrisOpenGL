#pragma once

#include <Bullet.h>

using namespace sdlFr;

namespace Galaga
{
    Bullet::Bullet(bool friendly)
    {
        mTimer = Timer::Instance();

        mTexture = new Texture("Bullet.png");
        mTexture->Parent(this);
        mTexture->Position(Vec2_Zero);
        mSpeed = 200;

        Reload();

        AddCollider(new BoxCollider(mTexture->ScaledDimensions()));
        mId = PhysicsManager::Instance()->RegisterEntity(this,
            friendly
            ? PhysicsManager::CollisionLayers::FriendlyProjectiles
            : PhysicsManager::CollisionLayers::HostileProjectiles);
    }

    Bullet::~Bullet()
    {
        mTimer = nullptr;

        delete mTexture;
        mTexture = nullptr;
    }

    void Bullet::Fire(Vector2 pos)
    {
        Position(pos);
        Active(true);
    }

    void Bullet::Reload()
    {
        Active(false);
    }

    void Bullet::Render()
    {
        if (Active())
        {
            mTexture->Render();
            PhysEntity::Render();
        }
    }

    void Bullet::Update()
    {
        if (Active())
        {
            Translate(Vec2_Down * mSpeed * mTimer->DeltaTime());
            Vector2 pos = Position();

            if (pos.y < -OFFSCREEN_BUFFER)
            {
                Reload();
            }
        }
    }

    bool Bullet::IgnoreCollisions()
    {
        return !Active();
    }

    void Bullet::Hit(PhysEntity* other) {
        Reload();
    }

}