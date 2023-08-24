#include <GLGraphics.h>

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
		float x = -1; //xPos
		float y = -1; //yPos
		float w = 1; //Width
		float h = 1; //Height

		if (texture.ID == 0)
		{
			glGenBuffers(1, &(texture.ID));
		}

		float vertexData[12];
		//First triangle
		vertexData[0] = x + w;
		vertexData[1] = y + h;
		vertexData[2] = x;
		vertexData[3] = y + h;
		vertexData[4] = x;
		vertexData[5] = y;
		//Second Triangle
		vertexData[6] = x;
		vertexData[7] = y;
		vertexData[8] = x + w;
		vertexData[9] = y;
		vertexData[10] = x + w;
		vertexData[11] = y + h;

		glBindBuffer(GL_ARRAY_BUFFER, texture.ID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(0);
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
		
		return true;
	}

	GLGraphics* GLGraphics::Instance()
	{
		if (sInstance == nullptr) 
		{
			sInstance = new GLGraphics();
		}
		return static_cast<GLGraphics*>(sInstance);
	}
}
