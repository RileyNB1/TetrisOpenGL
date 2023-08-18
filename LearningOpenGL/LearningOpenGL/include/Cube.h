#pragma once


#include <Macros.h>

#include <Window.h>
#include <Shader.h>

namespace FOGrP
{
	class Cube
	{
        Vertex mTris[3];
        Shader* mShader;

        //ID of Vertex Attribute
        GLuint positionID, colorID, normalID;
        //A buffer ID
        GLuint bufferID, elementID, arrayID;
        //ID of Uniform
        GLuint modelID, viewID, projectionID;

        Window* mWindow;

        glm::mat4 model, view, proj;

    public:

        Cube();

        void Init(Window* window);

        void BindVertexData();

        void Draw();

        ~Cube();
	};
}

