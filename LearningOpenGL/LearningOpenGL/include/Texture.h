#pragma once

#include <Macros.h>
#include <Shader.h>
#include <Window.h>
#include <vector>
#include <Bitmap.cpp>

namespace FOGrP
{
	struct TexVertex 
	{
		glm::vec2 position;
		glm::vec2 textureCoordinate;
	};

	class Texture
	{
		int th, tw;

		Shader* mShader;
		Window* mWindow;

		GLuint tID;
		GLuint arrayID;
		GLuint bufferID;
		GLuint positionID;
		GLuint textureCoordinateID;
		GLuint samplerID;

	public:

		Texture();

		void Init(Window* window);

		void BindVertexData();

		void Draw();

		~Texture();

	};
}

