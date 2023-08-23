#pragma once

#include <StartScreen.h>

namespace Galaga
{
    StartScreen::StartScreen()
    {
        mTimer = Timer::Instance();
        mInput = InputManager::Instance();

        //empty holder
        mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 80.0f);

        mPlayerOne = new SDLTexture("1UP", "emulogic.ttf", 32, { 200, 0, 0 });
        mPlayerTwo = new SDLTexture("2UP", "emulogic.ttf", 32, { 200, 0, 0 });
        mHiScore = new SDLTexture("HI SCORE", "emulogic.ttf", 32, { 200, 0, 0 });

        mTopBar->Parent(this);

        mPlayerOne->Parent(mTopBar);
        mPlayerTwo->Parent(mTopBar);
        mHiScore->Parent(mTopBar);

        mPlayerOne->Position(-Graphics::SCREEN_WIDTH * 0.35f, 0.0f);
        mPlayerTwo->Position(Graphics::SCREEN_WIDTH * 0.2f, 0.0f);
        mHiScore->Position(-30.0f, 0.0f);

        //***********************************************************

        mPlayModes = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f,
            Graphics::SCREEN_HEIGHT * 0.55f);
        mOnePlayerMode = new SDLTexture("1 Player ", "emulogic.ttf", 32, { 230, 230, 230 });
        mTwoPlayerMode = new SDLTexture("2 Players", "emulogic.ttf", 32, { 230, 230, 230 });
        mCursor = new SDLTexture("Cursor.png");

        mPlayModes->Parent(this);

        mOnePlayerMode->Parent(mPlayModes);
        mTwoPlayerMode->Parent(mPlayModes);
        mCursor->Parent(mPlayModes);

        mOnePlayerMode->Position(0.0f, -35.0f);
        mTwoPlayerMode->Position(0.0f, 35.0f);
        mCursor->Position(-175.0f, -35.0f);

        mCursor->Scale(Vector2(0.05, 0.05));
        mCursor->Position(mOnePlayerMode->Position(World) - Vector2(300, 85));

        //*****************************************************************8

        mBottomBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f,
            Graphics::SCREEN_HEIGHT * 0.7f);

        mNamco = new SDLTexture("namcot", "namco__.ttf", 36, { 200, 0, 0 });
        mDates = new SDLTexture("1981 1985 NAMCO LTD.", "emulogic.ttf", 32, { 230, 230, 230 });
        mRights = new SDLTexture("ALL RIGHTS RESERVED", "emulogic.ttf", 32, { 230, 230, 230 });

        mBottomBar->Parent(this);

        mNamco->Parent(mBottomBar);
        mDates->Parent(mBottomBar);
        mRights->Parent(mBottomBar);

        mNamco->Position(Vec2_Zero);
        mDates->Position(0.0f, 90.0f);
        mRights->Position(0.0f, 170.0f);

        //*******************************************************************
        mLogo = new SDLTexture("GalagaLogo.png");
        mLogo->Parent(this);
        mLogo->Position(mPlayModes->Position(World) - Vector2(0, 100));
        mLogo->Scale(Vector2(0.4f, 0.4f));

        mAnimationStartPos = Vector2(0.0f, Graphics::SCREEN_HEIGHT);
        mAnimationEndPos = Vec2_Zero;
        mAnimationTotalTime = 5.0f;
        mAnimationTimer = 0.0f;
        mAnimationDone = false;

        mCursorStartPos = mCursor->Position(Local);
        mCursorOffset = Vector2(0.0f, 70.0f);
        mSelectedMode = 0;

        //**************************************************************
        // top bar entities ... 
        mPlayerOneScore = new Scoreboard();
        mPlayerTwoScore = new Scoreboard();
        mTopScore = new Scoreboard();

        mPlayerOneScore->Parent(mPlayerOne);
        mPlayerTwoScore->Parent(mPlayerTwo);
        mTopScore->Parent(mHiScore);

        mPlayerOneScore->Position(mPlayerOne->Position(World) + Vector2(0, 80));
        mPlayerTwoScore->Position(mPlayerTwo->Position(World) + Vector2(0, 80));
        mTopScore->Position(mHiScore->Position(World) + Vector2(0, 80));

        mPlayerOneScore->Score(0);
        mPlayerTwoScore->Score(0);
        mTopScore->Score(645987);

        mStars = BackgroundStars::Instance();
        mStars->Scroll(true);
    }

    StartScreen::~StartScreen()
    {
        // top bar entities 
        delete mTopBar;
        mTopBar = nullptr;

        delete mPlayerOne;
        mPlayerOne = nullptr;

        delete mPlayerTwo;
        mPlayerTwo = nullptr;

        delete mHiScore;
        mHiScore = nullptr;

        // play mode entities 
        delete mPlayModes;
        mPlayModes = nullptr;

        delete mOnePlayerMode;
        mOnePlayerMode = nullptr;

        delete mTwoPlayerMode;
        mTwoPlayerMode = nullptr;

        delete mCursor;
        mCursor = nullptr;

        // bottom bar entities 
        delete mBottomBar;
        mBottomBar = nullptr;

        delete mNamco;
        mNamco = nullptr;

        delete mDates;
        mDates = nullptr;

        delete mRights;
        mRights = nullptr;

        // logo entities 
        delete mLogo;
        mLogo = nullptr;

        delete mPlayerOneScore;
        mPlayerOneScore = nullptr;

        delete mPlayerTwoScore;
        mPlayerTwoScore = nullptr;

        delete mTopScore;
        mTopScore = nullptr;

        mTimer = nullptr;
        mInput = nullptr;
    }

    void StartScreen::Update()
    {
        if (mAnimationDone)
        {
            if (mInput->KeyPressed(SDL_SCANCODE_DOWN))
            {
                ChangeSelectedMode(1);
            }
            else if (mInput->KeyPressed(SDL_SCANCODE_UP))
            {
                ChangeSelectedMode(-1);
            }
        }
        else if (mInput->KeyPressed(SDL_SCANCODE_DOWN) || mInput->KeyPressed(SDL_SCANCODE_UP))
        {
            mAnimationTimer = mAnimationTotalTime;
        }

        if (!mAnimationDone)
        {
            mAnimationTimer += mTimer->DeltaTime();
            if (mAnimationTimer >= mAnimationTotalTime)
            {
                mAnimationDone = true;
                return;
            }
            //mAnimationTimer += mTimer->DeltaTime();
            Position(Lerp(mAnimationStartPos, mAnimationEndPos,
                mAnimationTimer / mAnimationTotalTime));
        }

        mStars->Update();
    }

    void StartScreen::Render()
    {
        mStars->Render();

        mPlayerOne->Render();
        mPlayerTwo->Render();
        mHiScore->Render();

        mOnePlayerMode->Render();
        mTwoPlayerMode->Render();
        mCursor->Render();

        mNamco->Render();
        mDates->Render();
        mRights->Render();

        mLogo->Render();

        mPlayerOneScore->Render();
        mPlayerTwoScore->Render();
        mTopScore->Render();
    }

    void StartScreen::ChangeSelectedMode(int change)
    {
        mSelectedMode += change;
        if (mSelectedMode < 0)
        {
            mSelectedMode = 1;
        }
        else if (mSelectedMode > 1)
        {
            mSelectedMode = 0;
        }
        mCursor->Position(mCursorStartPos + mCursorOffset * (float)mSelectedMode);
    }

    void StartScreen::ResetAnimation()
    {
        mAnimationStartPos = Vector2(0.0f, Graphics::SCREEN_HEIGHT);
        mAnimationEndPos = Vec2_Zero;
        mAnimationTotalTime = 5.0f;

        mAnimationTimer = 0.0f; mAnimationDone = false;
        Position(mAnimationStartPos);
        mCursorStartPos = mCursor->Position(Local);

        mCursorOffset = Vector2(0.0f, 70.0f);
        mSelectedMode = 0;
    }

    int StartScreen::SelectedMode() { return mSelectedMode; }
}