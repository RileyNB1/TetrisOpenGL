#pragma once

#include <SDLMain.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>

namespace sdlFr
{
    class Graphics
    {
    public:
        static const short SCREEN_WIDTH = 800;
        static const short SCREEN_HEIGHT = 600;

        static Graphics* Instance();
        static void Release();
        static bool Initialized();

        void virtual ClearBackBuffer() = 0;
        void virtual Render() = 0;

        SDL_Texture* LoadTexture(std::string path);
        
        virtual void DrawTexture(SDL_Texture* tex,
            SDL_Rect* srcRect = nullptr,
            SDL_Rect* dstRect = nullptr,
            float angle = 0.0f,
            SDL_RendererFlip flip = SDL_FLIP_NONE);

        SDL_Texture* CreateTextTexture(TTF_Font* font,
            std::string text,
            SDL_Color color);

        void DrawLine(float startX, float startY, float endX, float endY);
        void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    protected:
        static Graphics* sInstance;
        static bool sInitialized;

        SDL_Window* mWindow;
        SDL_Renderer* mRenderer; 
        SDL_GLContext glContext;

        Graphics();
        ~Graphics();
        bool virtual Init();
    };
}
