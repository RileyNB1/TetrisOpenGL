#include <Graphics.h>
#include <SDLGraphics.h>

namespace sdlFr
{
    Graphics* Graphics::sInstance;
    bool Graphics::sInitialized;

    Graphics* Graphics::Instance()
    {
        if (sInstance == nullptr)
        {
            sInstance = new SDLGraphics();
        }
        return sInstance;
    }

    void Graphics::Release()
    {
        delete sInstance;
        sInstance = nullptr;
        sInitialized = false;
    }

    bool Graphics::Initialized()
    {
        return sInitialized;
    }

    Graphics::Graphics() : mRenderer(nullptr)
    {
        sInitialized = Init();
    }

    Graphics::~Graphics()
    {
        SDL_DestroyRenderer(mRenderer);
        SDL_DestroyWindow(mWindow);
    }

    bool Graphics::Init()
    {
        if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
        {
            std::cerr << "Unable to initialize SDL! SDL Error: "
                << SDL_GetError() << std::endl;
            return false;
        }

        if (TTF_Init() == -1)
        {
            std::cerr << "Unable to initialized SDL_ttf! TTF Error: "
                << TTF_GetError() << std::endl;
            return false;
        }

        mWindow = SDL_CreateWindow("SDL Tutorial", // window title 
            SDL_WINDOWPOS_UNDEFINED, // window x pos 
            SDL_WINDOWPOS_UNDEFINED, // window y pos 
            SCREEN_WIDTH, // window width 
            SCREEN_HEIGHT, // window height 
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL); // window flags 

        glContext = SDL_GL_CreateContext(mWindow);
        if (glContext == nullptr) {
            std::cerr << "SDL_GL context could not be created! " << SDL_GetError()
                << std::endl;
        }
        GLenum error = glewInit();
        if (error != GLEW_OK) {
            std::cerr << "Could not initialize glew! " << glewGetErrorString(error)
                << std::endl;
        }

        if (mWindow == nullptr)
        {
            std::cerr << "Unable to create Window! SDL Error: "
                << SDL_GetError() << std::endl;
            return false;
        }

        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

        if (mRenderer == nullptr)
        {
            std::cerr << "Unable to create renderer! SDL Error: "
                << SDL_GetError() << std::endl;
            return false;
        }

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        return true;
    }

    SDL_Texture* Graphics::LoadTexture(std::string path)
    {
        SDL_Texture* tex = nullptr;
        SDL_Surface* surface = IMG_Load(path.c_str());


        if (surface == nullptr)
        {
            std::cerr << "Unable to load " << path << ". IMG Error: "
                << IMG_GetError() << std::endl;
            return nullptr;
        }
        tex = SDL_CreateTextureFromSurface(mRenderer, surface);
        if (tex == nullptr)
        {
            std::cerr << "Unable to create texture from surface! IMG Error: "
                << IMG_GetError() << std::endl; SDL_FreeSurface(surface);
            return nullptr;
        }

        SDL_FreeSurface(surface);
        return tex;
    }

    void Graphics::DrawTexture(SDL_Texture* tex,
        SDL_Rect* srcRect,
        SDL_Rect* dstRect,
        float angle,
        SDL_RendererFlip flip)
    {
        /**/
    }

    SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font,
        std::string text,
        SDL_Color color)
    {
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

        if (surface == nullptr)
        {
            std::cerr << "CreateTextTexture:: TTF_RenderText_Solid Error: "
                << TTF_GetError() << std::endl;

            return nullptr;
        }

        SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface);

        if (tex == nullptr)
        {
            std::cerr << "CreateTextTexture:: SDL_CreateTextureFromSurface Error: "
                << SDL_GetError() << std::endl;

            return nullptr;
        }

        SDL_FreeSurface(surface);

        return tex;
    }

    void Graphics::DrawLine(float startX, float startY, float endX, float endY)
    {
        SDL_Color color;
        SDL_GetRenderDrawColor(mRenderer, &color.r, &color.g, &color.b, &color.a);
        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

        SDL_RenderDrawLine(mRenderer, (int)startX, (int)startY, (int)endX, (int)endY);

        SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
    }

    void Graphics::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        SDL_SetRenderDrawColor(mRenderer, r, g, b, a);
    }
}