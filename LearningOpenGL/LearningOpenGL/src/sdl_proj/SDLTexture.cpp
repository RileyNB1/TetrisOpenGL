#include <SDLTexture.h>

namespace sdlFr
{
    SDLTexture::SDLTexture(std::string filename, bool managed) : Texture(filename, managed)
    {
        
    }

    SDLTexture::SDLTexture(std::string filename,
        int x, int y, int w, int h,
        bool managed) : Texture(filename,
            x, y, w, h,
            managed)
    {
       
    }

    SDLTexture::SDLTexture(std::string text,
        std::string fontPath,
        int size, SDL_Color color,
        bool managed) : Texture(text,
            fontPath,
            size, color,
            managed)
    {
        
    }

    SDLTexture::~SDLTexture()
    {
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
        Texture::Render();
    }
}