#pragma once

#include <Texture.h>
#include <vector>

using namespace sdlFr;

namespace Galaga
{
    class Scoreboard : public GameEntity
    {
    private:
        std::vector<Texture*> mScore;
        SDL_Color mColor;
        void ClearBoard();
        const float size = 32;

    public:
        Scoreboard();
        Scoreboard(SDL_Color color);

        ~Scoreboard();

        void Score(int score);
        void Render();
    };

}