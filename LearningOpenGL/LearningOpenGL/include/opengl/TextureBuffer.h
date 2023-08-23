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

	class TextureBuffer
	{
		GLuint tID;
		int width, height;
	public:
		TextureBuffer(int w, int h);
		void Init();
		void BindVertexData();
		void Update(void* data);
		void Draw();
		void Bind();
		void Unbind();
		~TextureBuffer();
	};
}