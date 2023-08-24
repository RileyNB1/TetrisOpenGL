#include <GLTexture.h>
#include <GLGraphics.h>

namespace FOGrP
{
	GLTexture::GLTexture(std::string filename, bool managed) : Texture(filename, managed)
	{
	}

	GLTexture::GLTexture(std::string filename, int x, int y, int w, int h, bool managed) : Texture(filename,
		x, y, w, h,
		managed)
	{
	}

	GLTexture::GLTexture(std::string text, std::string fontPath, int size, SDL_Color color, bool managed) : Texture(text,
		fontPath,
		size, color,
		managed)
	{
	}

	GLTexture::~GLTexture()
	{
	}

	void GLTexture::Render()
	{
		Texture::Render();
		GLGraphics::Instance()->DrawSprite(*this, mClipped ? &mSourceRect : nullptr,
			&mDestinationRect, Rotation(World), Flip);
	}
}
