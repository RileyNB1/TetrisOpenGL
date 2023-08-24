#include <GLGraphics.h>
#include <managers/AssetManager.h>

namespace FOGrP
{
	GLGraphics::GLGraphics() : Graphics() 
	{
		sInitialized = Init();
	}
	
	GLGraphics::~GLGraphics() 
	{
		SDL_GL_DeleteContext(mWindow);
	}

	void GLGraphics::ClearBackBuffer()
	{
		glClearDepth(1.0);
		//clear the color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLGraphics::Render()
	{
		//Draw the triangle
		/*glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, -1.0f);
		glVertex2f(-1.0f, -1.0f);
		glEnd();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		SDL_GL_SwapWindow(mWindow);*/
	}

	void GLGraphics::DrawSprite(GLTexture& texture, SDL_Rect* srcRect, SDL_Rect* dstRect,
		float angle, SDL_RendererFlip flip)
	{
		//float x = -1; //xPos
		//float y = -1; //yPos
		//float w = 1; //Width
		//float h = 1; //Height

		//if (texture.ID == 0)
		//{
		//	glGenBuffers(1, &(texture.ID));
		//}

		//float vertexData[12];
		////First triangle
		//vertexData[0] = x + w;
		//vertexData[1] = y + h;
		//vertexData[2] = x;
		//vertexData[3] = y + h;
		//vertexData[4] = x;
		//vertexData[5] = y;
		////Second Triangle
		//vertexData[6] = x;
		//vertexData[7] = y;
		//vertexData[8] = x + w;
		//vertexData[9] = y;
		//vertexData[10] = x + w;
		//vertexData[11] = y + h;

		//glBindBuffer(GL_ARRAY_BUFFER, texture.ID);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);

		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		//glDisableVertexAttribArray(0);

		InitRenderData(&texture, srcRect, angle * DEG_TO_RAD,dstRect->x, dstRect->y, dstRect->w, dstRect->h,
			texture.ID);
		shaderUtil.Use();
		glGenBuffers(1, &texture.ID);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
		
		GLint location = shaderUtil.GetUniformLocation("tSampler");
		glUniform1i(location, 0);
		location = shaderUtil.GetUniformLocation("proj");
		glUniformMatrix4fv(location, 1, GL_FALSE, &(orthoMatrix[0][0]));

		glBindBuffer(GL_ARRAY_BUFFER, texture.ID);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(void*)offsetof(Vertex, position));
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex),
			(void*)offsetof(Vertex, color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(void*)offsetof(Vertex, uv));

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	bool GLGraphics::Init()
	{
		if (!Graphics::Init())
		{
			return false;
		}
		glContext = SDL_GL_CreateContext(mWindow);
		
		if (glContext == nullptr) 
		{
			std::cerr << "SDL_GL context could not be created!" <<
				SDL_GetError() << std::endl;
		}
		GLenum error = glewInit();
		if (error != GLEW_OK) {
			std::cerr << "Could not initialize glew!" <<
				glewGetErrorString(error) << std::endl;
		}
		//Enables a double buffer window - removes flickering.
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

		InitLoadShaderData();

		return true;
	}

	void GLGraphics::InitLoadShaderData()
	{
		shaderUtil = AssetManager::LoadShader("vs.shader", "fs.shader", nullptr,
			"sprite");
		orthoMatrix = glm::ortho(0.0f, (float)SCREEN_WIDTH,
			(float)SCREEN_HEIGHT, 0.0f, -1.0f, 1.0f);
		AssetManager::GetShader("sprite").Use().SetVector2f("vertexPosition",
			glm::vec2(0, 0));
		AssetManager::GetShader("sprite").SetMatrix4f("proj", orthoMatrix);
	}

	GLGraphics* GLGraphics::Instance()
	{
		if (sInstance == nullptr) 
		{
			sInstance = new GLGraphics();
		}
		return static_cast<GLGraphics*>(sInstance);
	}

	void GLGraphics::InitRenderData(Texture* texture, SDL_Rect* srcRect, float angle,
		float x, float y, float w, float h, GLuint quadVAO) {
		GLTexture* glTex = dynamic_cast<GLTexture*>(texture);
		if (!glTex) {
			std::cout << "TEXTURE ERROR" << std::endl;
			return;
		}
		float height = glTex->mSurface->h;
		float width = glTex->mSurface->w;
		if (quadVAO == 0)
		{
			glGenBuffers(1, &quadVAO);
		}
		
		glm::vec2 topRight = glm::vec2(1, 1);
		glm::vec2 topLeft = glm::vec2(0, 1);
		glm::vec2 BottomLeft = glm::vec2(0, 0);
		glm::vec2 BottomRight = glm::vec2(1, 0);
		
		if (srcRect) 
		{
			topRight = glm::vec2((srcRect->x + srcRect->w) / width,
				(srcRect->y + srcRect->h) / height);
			topLeft = glm::vec2(srcRect->x / width, (srcRect->y + srcRect->h) / height);
			BottomLeft = glm::vec2(srcRect->x / width, (srcRect->y) / height);
			BottomRight = glm::vec2((srcRect->x + srcRect->w) / width,
				(srcRect->y) / height);
		}
		Vertex vertexData[6];

		vertexData[0].SetPosition(x + w, y + h);
		vertexData[0].SetUV(topRight.x, topRight.y);
		vertexData[1].SetPosition(x, y + h);
		vertexData[1].SetUV(topLeft.x, topLeft.y);
		vertexData[2].SetPosition(x, y);
		vertexData[2].SetUV(BottomLeft.x, BottomLeft.y);
		vertexData[3].SetPosition(x, y);
		vertexData[3].SetUV(BottomLeft.x, BottomLeft.y);
		vertexData[4].SetPosition(x + w, y);
		vertexData[4].SetUV(BottomRight.x, BottomRight.y);
		vertexData[5].SetPosition(x + w, y + h);
		vertexData[5].SetUV(topRight.x, topRight.y);
		glBindBuffer(GL_ARRAY_BUFFER, quadVAO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}
