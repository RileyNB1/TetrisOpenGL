#pragma once

#include <vector>
#include <string>
#include <GameEntity.h>
#include <Graphics.h>

namespace sdlFr
{
    class Texture : public GameEntity
    {
    protected:

        SDL_Rect mSourceRect;
        SDL_Rect mDestinationRect;
        int mWidth; int mHeight;
        Graphics* mGraphics;
        SDL_Texture* mTex;

        bool mClipped;

    public:
        Texture(std::string filename, bool managed = false);

        Texture(std::string filename,
            int x, int y, int w, int h,
            bool managed = false);

        Texture(std::string text,
            std::string fontPath,
            int size,
            SDL_Color color,
            bool managed = false);

        virtual ~Texture();

        Vector2 ScaledDimensions();
        void SetSourceRect(SDL_Rect* sourceRect);
        void Render() override;
    };
}

