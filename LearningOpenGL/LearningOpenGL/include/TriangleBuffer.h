#pragma once

#include <Macros.h>

#include <vector>
#include <Window.h>
#include <Shader.h>

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
    glm::vec2 position;
    glm::vec4 color;
};

namespace FOGrP
{
    class TriangleBuffer
    {
        Vertex mTris[3];
        Shader *mTrisShader;

        //ID of Vertex Attribute
        GLuint positionID, colorID, orthoID;

        GLuint modelID, viewID, projectionID;
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

