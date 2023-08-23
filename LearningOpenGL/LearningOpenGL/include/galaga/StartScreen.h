#pragma once

#include <AnimatedTexture.h>
#include <GameEntity.h>
#include <managers/InputManager.h> 
#include <Scoreboard.h>
#include <BackgroundStars.h>

using namespace sdlFr;

namespace Galaga
{
    class StartScreen : public GameEntity
    {
    private:
        Timer* mTimer;
        InputManager* mInput;

        GameEntity* mTopBar;
        SDLTexture* mPlayerOne;
        SDLTexture* mPlayerTwo;
        SDLTexture* mHiScore;

        // Play Mode Entities 
        GameEntity* mPlayModes;
        SDLTexture* mOnePlayerMode;
        SDLTexture* mTwoPlayerMode;
        SDLTexture* mCursor;

        // Bottom Bar Entities 
        GameEntity* mBottomBar;
        SDLTexture* mNamco;
        SDLTexture* mDates;
        SDLTexture* mRights;

        SDLTexture* mLogo;

        Vector2 mAnimationStartPos;
        Vector2 mAnimationEndPos;
        float mAnimationTotalTime;
        float mAnimationTimer;
        bool mAnimationDone;

        // Play Mode Entities ... 
        Vector2 mCursorStartPos;
        Vector2 mCursorOffset;
        int mSelectedMode;

        Scoreboard* mPlayerOneScore;
        Scoreboard* mPlayerTwoScore;
        Scoreboard* mTopScore;

        BackgroundStars* mStars;

    public:
        StartScreen();
        ~StartScreen();

        void ResetAnimation();
        int SelectedMode();

        void ChangeSelectedMode(int change);

        void Update() override;
        void Render() override;
    };
}