#pragma once

#include <Graphics.h>
#include <GLTexture.h>
#include <ShaderUtil.h>

using namespace sdlFr;

namespace FOGrP
{
	class GLGraphics : public Graphics
	{
	private:
		SDL_GLContext glContext; 
		
		glm::mat4 orthoMatrix;

	protected:
		virtual bool Init() override; 
		
		void InitLoadShaderData();

		ShaderUtil shaderUtil;

	public:
		static GLGraphics* Instance();
		GLGraphics();
		~GLGraphics();

		virtual void ClearBackBuffer() override;
		virtual void Render() override; 

		void DrawSprite(GLTexture& texture, SDL_Rect* srcRect, SDL_Rect* dstRect,
			float angle, SDL_RendererFlip flip);

		void InitRenderData(Texture* texture, SDL_Rect* srcRect, float angle, float x,
			float y, float w, float h, GLuint quadVAO);
	};
}