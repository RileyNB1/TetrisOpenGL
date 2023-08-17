#pragma once

#include <GL_Lib.h>

#include <vector>
#include <Window.h>
#include <Shader.h>

//macro to write shader programs inline
#ifndef GLSL 
#define GLSL(version,A) "#version " #version "\n" #A
#endif

//macro to pick the right glGenVertexArray function
#ifndef GENVERTEXARRAYS
#define GENVERTEXARRAYS(n,id) \
  if(GLEW_APPLE_vertex_array_object) glGenVertexArraysAPPLE(1,id);\
	else if (GLEW_ARB_vertex_array_object) glGenVertexArrays(n,id)
#endif

//macro to pick the right glBindVertexArray function
#ifndef BINDVERTEXARRAY
#define BINDVERTEXARRAY(id) \
  if(GLEW_APPLE_vertex_array_object) glBindVertexArrayAPPLE(id);\
	else if (GLEW_ARB_vertex_array_object) glBindVertexArray(id)
#endif

class Vertex
{
public:
    glm::vec2 position;
    glm::vec4 color;
};

namespace FOGrP
{
    class TriangleBuffer
    {
        std::vector<Vertex> mTris;
        Shader *mTrisShader;

        //ID of Vertex Attribute
        GLuint positionID, colorID;
        //A buffer ID
        GLuint bufferID;
        //A Vertex Array ID
        GLuint arrayID;

    public:

        TriangleBuffer();

        void Init();

        void BindVertexData();

        void Draw(const Window& window);

        ~TriangleBuffer();
    };
}

