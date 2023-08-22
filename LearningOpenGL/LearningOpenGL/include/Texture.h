#pragma once

#include <Macros.h>
#include <Shader.h>
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
		GLuint tID;
		int width, height;

	public:

		Texture(int w, int h);

		void Init();

		void BindVertexData();

		void Update(void* data);

		void Draw();

		void Bind();

		void Unbind();

		~Texture();

	};
}

