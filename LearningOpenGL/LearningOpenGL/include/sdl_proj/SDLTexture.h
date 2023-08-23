#pragma once

#include <Texture.h>

namespace sdlFr
{
    class SDLTexture : public Texture
    {
    protected:

        SDL_Rect mSourceRect;
        SDL_Rect mDestinationRect;
        int mWidth; int mHeight;
        Graphics* mGraphics;
        SDL_Texture* mTex;

        bool mClipped;

    public:
        SDLTexture(std::string filename, bool managed = false);

        SDLTexture(std::string filename,
            int x, int y, int w, int h,
            bool managed = false);

        SDLTexture(std::string text,
            std::string fontPath,
            int size,
            SDL_Color color,
            bool managed = false);

        ~SDLTexture();

        Vector2 ScaledDimensions();
        void SetSourceRect(SDL_Rect* sourceRect);
        void Render() override;
    };
}