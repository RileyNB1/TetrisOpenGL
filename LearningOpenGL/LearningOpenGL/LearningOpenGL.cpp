#include <iostream>
#include <OpenGLApp.h>
#include <managers/GameManager.h>

using namespace sdlFr;

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
}