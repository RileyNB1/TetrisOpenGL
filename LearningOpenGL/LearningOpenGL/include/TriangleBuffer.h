#pragma once

#include <GL_Lib.h>

#include <vector>
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

/*-----------------------------------------------------------------------------
 *  A PLAIN-OLD-DATA ("POD") Container for 2D Coordinates (eventually we'll use a
 *  library for this)
 *-----------------------------------------------------------------------------*/
class Vec2 
{
public:
    Vec2(float _x = 0, float _y = 0) : x(_x), y(_y){}
    float x, y;
}; 

class Vec4 : public Vec2 
{
public:
    Vec4(float _x = 0, float _y = 0, float _z = 0, float _w = 0) 
        : Vec2(_x, _y)
    {

        z = _z;
        w = _w;
    }
    float z, w;
};

class Vertex
{
public:
    Vec2 position;
    Vec4 color;
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

        void Draw();

        ~TriangleBuffer();
    };
}

