#include <managers/GameManager.h>

namespace sdlFr
{
    GameManager* GameManager::sInstance = nullptr;

    GameManager* GameManager::Instance()
    {
        if (sInstance == nullptr)
        {
            sInstance = new GameManager();
        }
        return sInstance;
    }

    void GameManager::Release()
    {
        delete sInstance;
        sInstance = nullptr;
    }

    void GameManager::Run()
    { // main game loop 
        while (!mQuit)
        {
            mTimer->Update();

            if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE)
            {
                mTimer->Reset();
                Update();
                LateUpdate();
                Render();
            }

            // event processing loop 
            while (SDL_PollEvent(&mEvent))
            {
                switch (mEvent.type)
                {
                case SDL_QUIT:
                    mQuit = true;
                    break;
                }
            }
            Update();
            LateUpdate();
            Render();
        }
    }

    void GameManager::Update()
    {
        mInputManager->Update();

        mScreenManager->Update();

        if (mInputManager->KeyDown(SDL_SCANCODE_1))
        {
            mAudioManager->PlaySFX("bling.wav", 0, -1);
        }
    }

    void GameManager::LateUpdate()
    {
        mInputManager->UpdatePrevInput();
        mPhysicsManager->Update();
    }

    void GameManager::Render()
    {
        mGraphics->ClearBackBuffer();

        mScreenManager->Render();

        mGraphics->Render();
    }

    void GameManager::TestStuff()
    {
    }

    GameManager::GameManager() : mQuit(false)
    {
        // create Graphics singleton 
        mEvent = {};

        mGraphics = Graphics::Instance();
        mTimer = Timer::Instance();
        mInputManager = InputManager::Instance();
        mAudioManager = AudioManager::Instance();
        mAssetManager = AssetManager::Instance();
        mScreenManager = ScreenManager::Instance();
        mPhysicsManager = PhysicsManager::Instance();

        // verify Graphics module is ready 
        if (!Graphics::Initialized())
        {
            mQuit = true;
        }

        mPhysicsManager->SetLayerCollisionMask(
            PhysicsManager::CollisionLayers::Friendly,
            PhysicsManager::CollisionFlags::Hostile |
            PhysicsManager::CollisionFlags::HostileProjectiles);

        mPhysicsManager->SetLayerCollisionMask(
            PhysicsManager::CollisionLayers::FriendlyProjectiles,
            PhysicsManager::CollisionFlags::Hostile);

        mPhysicsManager->SetLayerCollisionMask(
            PhysicsManager::CollisionLayers::Hostile,
            PhysicsManager::CollisionFlags::Friendly |
            PhysicsManager::CollisionFlags::FriendlyProjectiles);

        mPhysicsManager->SetLayerCollisionMask(
            PhysicsManager::CollisionLayers::HostileProjectiles,
            PhysicsManager::CollisionFlags::Friendly);

        TestStuff();
    }

    GameManager::~GameManager()
    {
        // release modules 

        Graphics::Release();
        mGraphics = nullptr;

        Timer::Release();
        mTimer = nullptr;

        AssetManager::Release();
        mAssetManager = nullptr;

        InputManager::Release();
        mInputManager = nullptr;

        AudioManager::Release();
        mAudioManager = nullptr;

        ScreenManager::Release();
        mScreenManager = nullptr;

        mPhysicsManager->Release();
        mPhysicsManager = nullptr;

        // Quit SDL subsystems 
        SDL_Quit();
    }
}