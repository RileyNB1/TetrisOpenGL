#pragma once

#include <SDLMain.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>

namespace FOGrP
{
	class Texture;
	class Graphics
	{
	public:
		enum class RenderMode {
			SDL,
			GL
		};

		static const short SCREEN_WIDTH = 1024;
		static const short SCREEN_HEIGHT = 896;
		const char* WINDOW_TITLE = "Main Menu";

	protected:
		static Graphics* sInstance;
		static bool sInitialized;
		static RenderMode sMode;

		SDL_Window* mWindow;
		SDL_Renderer* mRenderer;

		SDL_GLContext mGLContext;

	public:
		static void SetMode(RenderMode mode);
		static Graphics* Instance();
		static void Release();
		static bool Initialized();

		SDL_Texture* LoadTexture(std::string path);
		SDL_Surface* LoadSurface(std::string path);
		SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);
		SDL_Surface* CreateTextSurface(TTF_Font* font, std::string text, SDL_Color color);

		virtual void DrawSprite(Texture* texture, SDL_Rect* srcRect = nullptr, SDL_Rect* dstRect = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
		
		virtual void DrawTexture(SDL_Texture* texture, SDL_Rect* srcRect = nullptr, SDL_Rect* dstRect = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
		
		void DrawLine(float startX, float startY, float endX, float endY);

		virtual void ClearBackBuffer();
		virtual void Render();

	protected:
		Graphics();
		~Graphics();

		virtual bool Init();
	};
}
