#pragma once

#include <Scoreboard.h>

namespace Galaga
{
    void Scoreboard::ClearBoard() 
    { 
        for (unsigned i = 0; i < mScore.size(); i++) 
        { 
            delete mScore[i]; 
            mScore[i] = nullptr; 
        } 
        
        mScore.clear(); 
    }

    void Scoreboard::Score(int score) 
    { 
        ClearBoard(); 
        
        if (score == 0) 
        { 
            for (int i = 0; i < 2; i++) 
            { 
                mScore.push_back(new Texture("0", "emulogic.ttf", size, mColor));
                mScore[i]->Parent(this); 
                mScore[i]->Position(Vector2(-size * i, 0.0f));
            }

            return;
        }
        std::string str = std::to_string(score);

        unsigned lastIndex = (unsigned)str.length() - 1;

        for (unsigned i = 0; i <= lastIndex; i++)
        {
            mScore.push_back(new Texture(str.substr(i, 1), "emulogic.ttf", size, mColor));
            mScore[i]->Parent(this);

            mScore[i]->Position(Vector2(-size * (lastIndex - i), 0.0f));
        }
    }

    Scoreboard::Scoreboard() : Scoreboard({ 230, 230, 230 }) 
    {

    }
    
    Scoreboard::Scoreboard(SDL_Color color) 
    { 
        mColor = color; 
        Score(0); 
    } 
    
    Scoreboard::~Scoreboard() 
    { 
        ClearBoard(); 
    }

    void Scoreboard::Render() 
    { 
        for (auto digit : mScore) 
        { 
            digit->Render(); 
        } 
    }
}