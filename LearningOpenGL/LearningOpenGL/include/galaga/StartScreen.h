#pragma once

#include <AnimatedTexture.h>
#include <GameEntity.h>
#include <managers/InputManager.h> 
#include <Scoreboard.h>
#include <BackgroundStars.h>

namespace Galaga
{
    class StartScreen : public GameEntity
    {
    private:
        Timer* mTimer;
        InputManager* mInput;

        GameEntity* mTopBar;
        GLTexture* mPlayerOne;
        GLTexture* mPlayerTwo;
        GLTexture* mHiScore;

        // Play Mode Entities 
        GameEntity* mPlayModes;
        GLTexture* mOnePlayerMode;
        GLTexture* mTwoPlayerMode;
        GLTexture* mCursor;

        // Bottom Bar Entities 
        GameEntity* mBottomBar;
        GLTexture* mNamco;
        GLTexture* mDates;
        GLTexture* mRights;

        GLTexture* mLogo;

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