#pragma once

#include <Graphics.h>
#include <GLTexture.h>

using namespace sdlFr;

namespace FOGrP
{
	class GLGraphics : public Graphics
	{
	private:
		SDL_GLContext glContext;

	protected:
		virtual bool Init() override;

	public:
		static GLGraphics* Instance();
		GLGraphics();
		~GLGraphics();

		virtual void ClearBackBuffer() override;
		virtual void Render() override; 

		void DrawSprite(GLTexture& texture, SDL_Rect* srcRect, SDL_Rect* dstRect,
			float angle, SDL_RendererFlip flip);
	};
}