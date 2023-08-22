#pragma once

#include <GameEntity.h>
#include <managers/AssetManager.h> 

namespace sdlFr
{
    class SDLTexture : public GameEntity
    {
    private:

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

    SDLTexture::SDLTexture(std::string filename, bool managed)
    {
        mGraphics = Graphics::Instance();

        mTex = AssetManager::Instance()->GetTexture(filename, managed);

        SDL_QueryTexture(mTex, nullptr, nullptr, &mWidth, &mHeight);

        mClipped = false;
        mDestinationRect.w = mWidth;
        mDestinationRect.h = mHeight;
    }

    SDLTexture::SDLTexture(std::string filename,
        int x, int y, int w, int h,
        bool managed)
    {
        mGraphics = Graphics::Instance();
        mTex = AssetManager::Instance()->GetTexture(filename, managed);

        mWidth = w;
        mHeight = h;
        mClipped = true;
        mDestinationRect.w = mWidth;
        mDestinationRect.h = mHeight;

        mSourceRect.x = x;
        mSourceRect.y = y;
        mSourceRect.w = mWidth;
        mSourceRect.h = mHeight;
    }

    SDLTexture::SDLTexture(std::string text,
        std::string fontPath,
        int size, SDL_Color color,
        bool managed)
    {
        mGraphics = Graphics::Instance();

        mTex = AssetManager::Instance()->
            GetText(text, fontPath, size, color, managed);

        mClipped = false;

        SDL_QueryTexture(mTex, nullptr, nullptr, &mWidth, &mHeight);

        mDestinationRect.w = mWidth;
        mDestinationRect.h = mHeight;
    }

    SDLTexture::~SDLTexture()
    {
        AssetManager::Instance()->DestroyTexture(mTex);
        mTex = nullptr;
        mGraphics = nullptr;
    }

    Vector2 SDLTexture::ScaledDimensions()
    {
        Vector2 scaledDimensions = Scale();
        scaledDimensions.x *= mWidth;
        scaledDimensions.y *= mHeight;

        return scaledDimensions;
    }

    void SDLTexture::SetSourceRect(SDL_Rect* sourceRect)
    {
        mSourceRect = *sourceRect;
    }

    void SDLTexture::Render()
    {
        Vector2 pos = Position(World);
        Vector2 scale = Scale(World);
        mDestinationRect.x = (int)(pos.x - mWidth * 0.5f);
        mDestinationRect.y = (int)(pos.y - mHeight * 0.5f);
        mDestinationRect.w = (int)(mWidth * scale.x);
        mDestinationRect.h = (int)(mHeight * scale.y);

        mGraphics->DrawTexture(mTex,
            mClipped ? &mSourceRect : nullptr,
            &mDestinationRect,
            Rotation(World));
    }
}