#include <SDLGraphics.h>

namespace FOGrP
{
	SDLGraphics* SDLGraphics::Instance()
	{
		if (sInstance == nullptr) 
		{
			sInstance = new SDLGraphics();
		}
		return static_cast<SDLGraphics*>(sInstance);
	}

	SDLGraphics::SDLGraphics()
	{
		sInitialized = Init();
	}

	void SDLGraphics::ClearBackBuffer()
	{
		SDL_RenderClear(mRenderer);
	}

	void SDLGraphics::Render()
	{
		SDL_RenderPresent(mRenderer);

		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnableClientState(GL_COLOR_ARRAY);

		/*glBegin(GL_TRIANGLES);


		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(0, 0);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0, 500);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(500, 500);

		glEnd();*/

		SDL_GL_SwapWindow(mWindow);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void SDLGraphics::DrawTexture(SDL_Texture* tex, SDL_Rect* srcRect, SDL_Rect* dstRect, float angle, SDL_RendererFlip flip)
	{
		SDL_RenderCopyEx(mRenderer,
			tex,
			srcRect,
			dstRect,
			angle,
			nullptr,
			flip);
	}

	bool SDLGraphics::Init()
	{
		return Graphics::Init();
	}
	
	SDLGraphics::~SDLGraphics() { }
}