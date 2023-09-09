#include "Tetris/StartScreen.h"


StartScreen::StartScreen()
{


    mStartButton = new GLTexture("Start", "emulogic.ttf", 32, { 200, 0, 0 });
    mTetrisLogo = new GLTexture("Tetris.png");

}

StartScreen::~StartScreen()
{

    delete mStartButton;
    mStartButton = nullptr;

    // logo entities 
    delete mTetrisLogo;
    mTetrisLogo = nullptr;


}

void StartScreen::Update()
{

}

void StartScreen::Render()
{


    mStartButton->Render();

    mTetrisLogo->Render();


}