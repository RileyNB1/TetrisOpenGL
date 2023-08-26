#pragma once

#include <vector>
#include <string>
#include <GameEntity.h>
#include <Graphics.h>

namespace FOGrP
{
	class Texture : public GameEntity {
	protected:
		SDL_Texture* mTex;
		Graphics* mGraphics;

		int mWidth;
		int mHeight;

		bool mClipped;
		SDL_Rect mSourceRect;
		SDL_Rect mDestinationRect;

	public:
		Texture(std::string filename, bool managed = true);
		Texture(std::string filename, int x, int y, int w, int h, bool managed = true);
		Texture(std::string text, std::string fontPath, int size, SDL_Color color, bool managed = true);
		virtual ~Texture();

		Vector2 ScaledDimensions();

		void SetSourceRect(SDL_Rect* sourceRect);

		virtual void Render() override;

	protected:
		void UpdateDstRect();
	};
}

