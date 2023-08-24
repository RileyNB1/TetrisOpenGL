#pragma once

#include <Graphics.h>

namespace sdlFr
{
	class SDLGraphics : public Graphics 
	{
	public:
		static SDLGraphics* Instance();
		SDLGraphics();

		void virtual ClearBackBuffer() override;
		void virtual Render() override;
		
		virtual void DrawTexture(SDL_Texture* tex,
			SDL_Rect* srcRect = nullptr,
			SDL_Rect* dstRect = nullptr,
			float angle = 0.0f,
			SDL_RendererFlip flip = SDL_FLIP_NONE) override;

		~SDLGraphics();

	protected:
		virtual bool Init() override;
	};
}

