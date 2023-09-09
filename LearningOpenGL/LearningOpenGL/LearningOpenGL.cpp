#include <iostream>
#include <cstdlib>
#include <OpenGLApp.h>
#include <managers/GameManager.h>

#define MAX_RAY_DEPTH 100
#define PI 3.1415926535




int main()
{
    /*FOGrP::OpenGLApp app;

    app.Start();

    return 0;*/

    GameManager* game = GameManager::Instance();
        game->Run();
        GameManager::Release(); 
        game = nullptr; 
        return 0;

   
    
    
    return 0;
}