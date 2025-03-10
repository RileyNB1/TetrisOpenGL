#pragma once

#include <GLGraphics.h> 
#include "Tetris/StartScreen.h"
#include <Timer.h>
#include <GameEntity.h>
#include <managers/AssetManager.h>
#include <managers/InputManager.h>
#include <AnimatedTexture.h>
#include <managers/AudioManager.h>
#include <managers/PhysicsManager.h>


namespace FOGrP
{
    class GameManager
    {
    private:
        // singleton 
        static GameManager* sInstance;
        // loop control 
        bool mQuit;
        
        // modules 
        Graphics* mGraphics;
        StartScreen* mStartScreen;
        AssetManager* mAssetManager;
        InputManager* mInputManager;
        AudioManager* mAudioManager;
  
        PhysicsManager* mPhysicsManager;

        SDL_Event mEvent;
        const int FRAME_RATE = 60;
        Timer* mTimer;

        //Test
        //End test
    public:
        static GameManager* Instance();
        static void Release();

        void Run();
        void Update();
        void LateUpdate();
        void Render();

        void TestStuff();

        GameManager();
        ~GameManager();
    };
}