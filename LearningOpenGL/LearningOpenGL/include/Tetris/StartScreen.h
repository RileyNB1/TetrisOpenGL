#pragma once
#include "GLTexture.h"
#include "GameEntity.h"

using namespace FOGrP;

class StartScreen : public GameEntity
{
private:
  

    
    GLTexture* mStartButton;
    GLTexture* mTetrisLogo;
  

public:
    StartScreen();
    ~StartScreen();


    void Update() override;
    void Render() override;
};