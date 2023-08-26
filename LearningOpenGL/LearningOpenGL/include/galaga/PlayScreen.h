#pragma once

#include <GameEntity.h>
#include <Timer.h>
#include <managers/AudioManager.h>
#include <BackgroundStars.h>
#include <PlaySideBar.h>
#include <Level.h>
#include <Player.h>

using namespace FOGrP;

namespace Galaga
{
    class PlayScreen : public GameEntity
    {
    private:
        Timer* mTimer;
        AudioManager* mAudio;
        BackgroundStars* mStars;
        PlaySideBar* mSideBar;

        Texture* mStartLabel;
        float mLevelStartTimer;
        float mLevelStartDelay;
        bool mGameStarted;
        Level* mLevel;
        bool mLevelStarted;
        int mCurrentStage;
        Player* mPlayer;

        void StartNextLevel();

    public:
        PlayScreen();
        ~PlayScreen();

        void StartNewGame();

        void Update() override;
        void Render() override;

        bool GameOver();
    };
}