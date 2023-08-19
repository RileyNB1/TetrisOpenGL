#pragma once

#include <Macros.h>
#include <Shader.h>
#include <Window.h>
#include <vector>

namespace FOGrP
{
    struct Vertex
    {
    public:
        glm::vec3 position;
        glm::vec4 color;
    };
	class DynamicMesh
	{
        Vertex mTris[3];
        Shader* mShader;

        //ID of Vertex Attribute
        GLuint positionID, colorID;
        //A buffer ID
        GLuint bufferID;
        //A Vertex Array ID
        GLuint arrayID;
        GLuint elementID;
        //ID of Uniform
        GLuint modelID, viewID, projectionID;

        Window* mWindow;

        glm::mat4 model, view, proj; 
        
        int w;
        int h;
        //A Container for Vertices
        std::vector<Vertex> vertices;
        //A Container for indices
        std::vector<unsigned short> indices;

    public:

        DynamicMesh();

        void Init(Window* window);

        void BindVertexData();

        void Draw();

        ~DynamicMesh();
	};
}

