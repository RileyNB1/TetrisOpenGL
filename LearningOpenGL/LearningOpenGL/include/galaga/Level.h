#pragma once

#include <Timer.h>
#include <PlaySideBar.h>
#include <BackgroundStars.h>
#include <Player.h>
#include <Butterfly.h>
#include <Wasp.h>
#include <Boss.h>

#include "tinyxml/tinyxml2.h" 

using namespace tinyxml2;
using namespace sdlFr;

namespace Galaga
{
    class Level : public GameEntity
    {
    public:
        enum LevelStates { Running, Finished, GameOver };

        Level(int stage, PlaySideBar* sideBar, Player* player);
        ~Level();

        void Update() override;
        void Render() override;

        LevelStates State();

    private:
        Timer* mTimer;
        PlaySideBar* mSideBar;
        BackgroundStars* mStars;

        int mStage;
        bool mStageStarted;

        float mLabelTimer;
        Texture* mStageLabel;
        Scoreboard* mStageNumber;
        float mStageLabelOnScreen;
        float mStageLabelOffScreen;
        Texture* mReadyLabel;
        float mReadyLabelOnScreen;
        float mReadyLabelOffScreen;
        Player* mPlayer;

        bool mPlayerHit;
        float mRespawnDelay;
        float mRespawnTimer;
        float mRespawnLabelOnScreen;

        Texture* mGameOverLabel;
        float mGameOverDelay;
        float mGameOverTimer;
        float mGameOverLabelOnScreen;

        void StartStage();

        LevelStates mCurrentState;
        void HandleStartLabels();
        void HandleCollisions();
        void HandlePlayerDeath();

        Formation* mFormation;
        std::vector<Enemy*> mEnemies;

        static const int MAX_BUTTERFLIES = 16;
        int mButterflyCount;
        Butterfly* mFormationButterflies[MAX_BUTTERFLIES];

        static const int MAX_WASPS = 20;
        int mWaspCount;
        Wasp* mFormationWasps[MAX_WASPS];

        static const int MAX_BOSSES = 4;
        int mBossCount;
        Boss* mFormationBosses[MAX_BOSSES];

        bool mChallengeStage;

        XMLDocument mSpawningPatterns;
        int mCurrentFlyInPriority;
        int mCurrentFlyInIndex;
        float mSpawnDelay;
        float mSpawnTimer;
        bool mSpawningFinished;

        Butterfly* mDivingButterfly;
        bool mSkipFirstButterfly;
        float mButterflyDiveDelay;
        float mButterflyDiveTimer;

        Wasp* mDivingWasp;
        Wasp* mDivingWasp2;
        float mWaspDiveDelay;
        float mWaspDiveTimer;

        Boss* mDivingBoss;
        bool mCaptureDive;
        bool mSkipFirstBoss;
        float mBossDiveDelay;
        float mBossDiveTimer;

        void HandleEnemySpawning();
        void HandleEnemyFormation();
        void HandleEnemyDiving();
        bool EnemyFlyingIn();

        void ButterfliesDiving();
        void WaspsDiving();
        void BossesDiving();
    };
}