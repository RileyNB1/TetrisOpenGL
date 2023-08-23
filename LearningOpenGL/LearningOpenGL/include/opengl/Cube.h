#pragma once

#include <Macros.h>

#include <Window.h>
#include <Shader.h>
#include <Bitmap.cpp>

namespace FOGrP
{

    struct CubeVert
    {
    public:
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec4 color;         //<-- Assign a color to the vertex
        glm::vec2 textureCoordinate; //<-- Assign a texture coordinate to the vertex

        //Memory Offsets
        static size_t offsetNormal() { return sizeof(glm::vec3); }
        static size_t offsetColor() { return sizeof(glm::vec3) * 2; }
        static size_t offsetTextureCoordinate() { return sizeof(glm::vec3) * 2 + sizeof(glm::vec4); }
    };

	class Cube
	{
        CubeVert mTris[3];
        Shader* mShader;

        //ID of Vertex Attribute
        GLuint positionID, colorID, normalID, textureCoordinateID;
        //A buffer ID
        GLuint bufferID, elementID, arrayID;

        Window* mWindow;

        MVP mvp;

        //Texture ID
        GLuint tID;
    public:

        Cube();

        void Init(Window* window, MVP& _mvp);

        void BindVertexData();

        void Draw();

        ~Cube();
	};
}

