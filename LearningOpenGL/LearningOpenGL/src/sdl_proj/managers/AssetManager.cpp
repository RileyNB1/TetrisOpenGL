#include <managers/AssetManager.h>
#include <fstream>

namespace sdlFr
{
    AssetManager* AssetManager::sInstance = nullptr;

    std::map<std::string, ShaderUtil> AssetManager::shaders;

    AssetManager* AssetManager::Instance()
    {
        if (sInstance == nullptr)
        {
            sInstance = new AssetManager();
        }
        return sInstance;
    }

    void AssetManager::Release()
    {
        delete sInstance;
        sInstance = nullptr;
    }

    AssetManager::AssetManager()
    { }

    AssetManager::~AssetManager()
    {
        for (auto tex : mTextures)
        {
            if (tex.second != nullptr)
            {
                SDL_DestroyTexture(tex.second);
            }
        }
        mTextures.clear();
    }

    SDL_Texture* AssetManager::GetTexture(std::string filename, bool managed)
    {
        std::string fullPath = SDL_GetBasePath();
        fullPath.append(/*"Assets\\" +*/ filename);

        if (mTextures[fullPath] == nullptr)
        {
            mTextures[fullPath] = Graphics::Instance()->LoadTexture(fullPath);
        }

        if (mTextures[fullPath] != nullptr && managed)
        {
            mTextureRefCount[mTextures[fullPath]] += 1;
        }
        return mTextures[fullPath];
    }

    void AssetManager::DestroyTexture(SDL_Texture* texture)
    {
        if (mTextureRefCount.find(texture) != mTextureRefCount.end())
        {
            mTextureRefCount[texture] -= 1;
            if (mTextureRefCount[texture] == 0)
            {
                for (auto elem : mTextures)
                {
                    if (elem.second == texture)
                    {
                        SDL_DestroyTexture(elem.second);
                        mTextures.erase(elem.first);
                        return; // work finished, leave function 
                    }
                }

                for (auto elem : mText)
                {
                    if (elem.second == texture)
                    {
                        SDL_DestroyTexture(elem.second);
                        mText.erase(elem.first);

                        return; // work finished, leave function 
                    }
                }
            }
        }
        else
        {
            SDL_DestroyTexture(texture);
        }
    }

    TTF_Font* AssetManager::GetFont(std::string filename, int size)
    {
        std::string fullPath = SDL_GetBasePath();
        fullPath.append(/*"Assets/" + */filename);

        std::stringstream ss;
        ss << size;
        std::string key = fullPath + ss.str();

        if (mFonts[key] == nullptr)
        {
            mFonts[key] = TTF_OpenFont(fullPath.c_str(), size);

            if (mFonts[key] == nullptr)
            {
                std::cerr << "Unable to load font " << filename
                    << "! TTF Error: " << TTF_GetError() << std::endl;
            }
        }
        return mFonts[key];
    }

    SDL_Texture* AssetManager::GetText(std::string text,
        std::string filename,
        int size,
        SDL_Color color, bool managed)
    {
        std::stringstream ss;
        ss << size
            << (int)color.r
            << (int)color.g
            << (int)color.b;

        std::string key = text + filename + ss.str();

        if (mText[key] == nullptr)
        {
            TTF_Font* font = GetFont(filename, size);
            mText[key] = Graphics::Instance()->CreateTextTexture(font, text, color);
        }

        if (mText[key] != nullptr && managed)
        {
            mTextureRefCount[mText[key]] += 1;
        }
        return mText[key];
    }

    Mix_Music* AssetManager::GetMusic(std::string filename, bool managed)
    {
        std::string fullPath = SDL_GetBasePath();
        fullPath.append(/*"Assets/" +*/ filename);

        if (mMusic[fullPath] == nullptr)
        {
            mMusic[fullPath] = Mix_LoadMUS(fullPath.c_str());
        }

        if (mMusic[fullPath] == nullptr)
        {
            std::cerr << "Unable to load music " << filename
                << "! Mix error: " << Mix_GetError() << std::endl;
        }
        else if (managed)
        {
            mMusicRefCount[mMusic[fullPath]] += 1;
        }

        return mMusic[fullPath];
    }

    Mix_Chunk* AssetManager::GetSFX(std::string filename, bool managed)
    {
        std::string fullPath = SDL_GetBasePath();

        fullPath.append(/*"Assets/" + */filename);

        if (mSFX[fullPath] == nullptr)
        {
            mSFX[fullPath] = Mix_LoadWAV(fullPath.c_str());
        }

        if (mSFX[fullPath] == nullptr)
        {
            std::cerr << "Unable to load SFX " << filename
                << "! Mix error: " << Mix_GetError() << std::endl;
        }
        else if (managed)
        {
            mSFXRefCount[mSFX[fullPath]] += 1;
        }

        return mSFX[fullPath];
    }

    void AssetManager::DestroyMusic(Mix_Music* music)
    {
        for (auto elem : mMusic)
        {
            if (elem.second == music)
            {
                mMusicRefCount[elem.second] -= 1;
                if (mMusicRefCount[elem.second] == 0)
                {
                    Mix_FreeMusic(elem.second); mMusic.erase(elem.first);
                }
                return; // work finished, leave function 
            }
        }
    }

    void AssetManager::DestroySFX(Mix_Chunk* sfx)
    {
        for (auto elem : mSFX)
        {
            if (elem.second == sfx)
            {
                mSFXRefCount[elem.second] -= 1;
                if (mSFXRefCount[elem.second] == 0)
                {
                    Mix_FreeChunk(elem.second);
                    mSFX.erase(elem.first);
                }
                return; // work finished, leave function 
            }
        }
    }

    SDL_Surface* AssetManager::GetSurfaceTexture(std::string filename, bool managed) 
    {
        std::string fullPath = SDL_GetBasePath();
        fullPath.append("Assets/" + filename);
        if (mSurfaceTextures[fullPath] == nullptr) 
        {
            mSurfaceTextures[fullPath] =
                Graphics::Instance()->GetSurfaceTexture(fullPath);
        }
        if (mSurfaceTextures[fullPath] != nullptr && managed) 
        {
            mSurfaceaceRefCount[mSurfaceTextures[fullPath]] += 1;
        }
        return mSurfaceTextures[fullPath];
    }
    
    SDL_Surface * AssetManager::GetSurfaceText(std::string text, std::string filename,
            int size, SDL_Color color, bool managed) 
    {
        std::stringstream ss;
        ss << size << (int)color.r << (int)color.g << (int)color.b;
        std::string key = text + filename + ss.str();
        if (mSurfaceText[key] == nullptr) 
        {
            TTF_Font* font = GetFont(filename, size);
            mSurfaceText[key] =
                Graphics::Instance()->GetSurfaceText(font, text, color);
        }
        if (mSurfaceText[key] != nullptr && managed) 
        {
            mSurfaceaceRefCount[mSurfaceText[key]] += 1;
        }
        return mSurfaceText[key];
    }

    void AssetManager::DestroySurface(SDL_Surface* surface)
    {
        if (mSurfaceaceRefCount.find(surface) != mSurfaceaceRefCount.end()) 
        {
            mSurfaceaceRefCount[surface] -= 1;
            if (mSurfaceaceRefCount[surface] == 0) 
            {
                for (auto elem : mSurfaceTextures) 
                {
                    if (elem.second == surface) 
                    {
                        SDL_FreeSurface(elem.second);
                        mSurfaceTextures.erase(elem.first);
                        return; // work finished, leave function
                    }
                }
                for (auto elem : mSurfaceText) 
                {
                    if (elem.second == surface) 
                    {
                        SDL_FreeSurface(elem.second);
                        mSurfaceText.erase(elem.first);
                        return; // work finished, leave function
                    }
                }
            }
        }
    }

    ShaderUtil AssetManager::LoadShader(const GLchar* vShaderFile, const GLchar*
        fShaderFile, const GLchar* gShaderFile, std::string name) {
        shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
        return shaders[name];
    }
    
    ShaderUtil AssetManager::GetShader(std::string name) {
        return shaders[name];
    }
    
    ShaderUtil AssetManager::loadShaderFromFile(const GLchar * vShaderFile,
            const GLchar * fShaderFile, const GLchar * gShaderFile /*= nullptr*/) {
        // 1. Retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;
        try {
            // Open files
            std::ifstream vertexShaderFile(vShaderFile);
            std::ifstream fragmentShaderFile(fShaderFile);
            std::stringstream vShaderStream, fShaderStream;
            // Read file's buffer contents into streams
            vShaderStream << vertexShaderFile.rdbuf();
            fShaderStream << fragmentShaderFile.rdbuf();
            // close file handlers
            vertexShaderFile.close();
            fragmentShaderFile.close();
            // Convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
            // If geometry shader path is present, also load a geometry shader
            if (gShaderFile != nullptr)
            {
                std::ifstream geometryShaderFile(gShaderFile);
                std::stringstream gShaderStream;
                gShaderStream << geometryShaderFile.rdbuf();
                geometryShaderFile.close();
                geometryCode = gShaderStream.str();
            }
        }
        catch (std::exception e) {
            std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
        }
        const GLchar* vShaderCode = vertexCode.c_str();
        const GLchar* fShaderCode = fragmentCode.c_str();
        const GLchar* gShaderCode = geometryCode.c_str();
        // 2. Now create shader object from source code
        ShaderUtil shader;
        shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ?
            gShaderCode : nullptr);
        return shader;
    }
}