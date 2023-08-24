#pragma once

#include <Texture.h>

using namespace  sdlFr;

namespace FOGrP
{
    class GLTexture : public Texture
    {
    protected:

    public:

        GLuint ID;
        GLuint Width, Height;
        GLuint Internal_Format;
        GLuint Image_Format;
        GLuint Wrap_S;
        GLuint Wrap_T;
        GLuint Filter_Min;
        GLuint Filter_Max;
        int mode;
        bool rendered;
        unsigned char* data;
        SDL_RendererFlip Flip;
        SDL_Surface* mSurfaceace;

        GLTexture(std::string filename, bool managed = false);

        GLTexture(std::string filename,
            int x, int y, int w, int h,
            bool managed = false);

        GLTexture(std::string text,
            std::string fontPath,
            int size,
            SDL_Color color,
            bool managed = false);

        ~GLTexture();

        void Render() override; 
    };
}

