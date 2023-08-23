#pragma once
#include <PhysEntity.h>
#include <Timer.h>
#include <managers/AudioManager.h>
#include <managers/InputManager.h>
#include <AnimatedTexture.h>
#include <Bullet.h>

using namespace sdlFr;

namespace Galaga
{
    class Player : public PhysEntity
    {
    private:

        Timer* mTimer;
        InputManager* mInput;
        AudioManager* mAudio;

        bool mVisible;
        bool mAnimating;
        int mScore;
        int mLives;
        Texture* mShip;
        AnimatedTexture* mDeathAnimation;
        float mMoveSpeed;
        Vector2 mMoveBounds;

        static const int MAX_BULLETS = 2;
        Bullet* mBullets[MAX_BULLETS];

        bool mWasHit;

        void HandleMovement();
        void HandleFiring();

        float mCollisionTimer;

    public:
        Player();
        ~Player();

        void Update() override;
        void Render() override;

        void Visible(bool visible);
        bool IsAnimating();
        int Score();
        int Lives();
        void AddScore(int change);
        bool WasHit(); 
        
        // Inherited from PhysEntity 
        bool IgnoreCollisions() override; 
        void Hit(PhysEntity * other) override;
    };

}