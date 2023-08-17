#include "TriangleBuffer.h"

namespace FOGrP
{

    /*-----------------------------------------------------------------------------
     *  SOME SHADER CODE
     *-----------------------------------------------------------------------------*/
    const char* vert = GLSL(120,

    attribute vec4 position;
    attribute vec4 color;

    varying vec4 dstColor;             //<-- new uniform matrix

    void main() {
        dstColor = color;
        gl_Position = position;  //<-- matrix gets multiplied by the position
    }

    );

    const char* frag = GLSL(120,

    varying vec4 dstColor;

    void main() {
        gl_FragColor = dstColor;
    }

    );

    TriangleBuffer::TriangleBuffer()
    {    
    }

    void FOGrP::TriangleBuffer::Init()
    {
        Vertex v1, v2, v3;

        v1.position = glm::vec2(-1, -0.5);
        v1.color = glm::vec4(1, 0, 0, 1);

        v2.position = glm::vec2(0, 1);
        v2.color = glm::vec4(0, 1, 0, 1);

        v3.position = glm::vec2(1, -0.5);
        v3.color = glm::vec4(0, 0, 1, 1);

        //Specify the 3 VERTICES of A Triangle
        mTris.push_back(v1);
        mTris.push_back(v2);
        mTris.push_back(v3);

        /*-----------------------------------------------------------------------------
         *  CREATE THE SHADER
         *-----------------------------------------------------------------------------*/

         //1. CREATE SHADER PROGRAM
        mTrisShader = new Shader(vert, frag);
    }

    void TriangleBuffer::BindVertexData()
    {
        positionID = glGetAttribLocation(mTrisShader->Id(), "position");
        colorID = glGetAttribLocation(mTrisShader->Id(), "color");

        glUseProgram(0);


        //| x | y | r | g | b | a| |x | y | r | g | b | a| |x | y | r | g | b | a |
            /*-----------------------------------------------------------------------------
             *  CREATE THE VERTEX ARRAY OBJECT
             *-----------------------------------------------------------------------------*/
        GENVERTEXARRAYS(1, &arrayID);
        BINDVERTEXARRAY(arrayID);

        /*-----------------------------------------------------------------------------
         *  CREATE THE VERTEX BUFFER OBJECT
         *-----------------------------------------------------------------------------*/
         // Generate one buffer
        glGenBuffers(1, &bufferID);
        // Bind Array Buffer 
        glBindBuffer(GL_ARRAY_BUFFER, bufferID);
        // Send data over buffer to GPU
        glBufferData(GL_ARRAY_BUFFER, mTris.size() * sizeof(Vertex), &(mTris[0]), GL_STATIC_DRAW);


        /*-----------------------------------------------------------------------------
         *  ENABLE VERTEX ATTRIBUTES
         *-----------------------------------------------------------------------------*/
         // Enable Position Attribute
        glEnableVertexAttribArray(positionID);
        // Enable Color Attribute
        glEnableVertexAttribArray(colorID);

        // Tell OpenGL how to handle the buffer of data that is already on the GPU
        glVertexAttribPointer(positionID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec2));

        BINDVERTEXARRAY(0);

        /// <summary>
        /// Not in colored tris buffer
        /// </summary>
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void TriangleBuffer::Draw(const Window& window)
    {
        //Bind Shader and Vertex Array Object
        glUseProgram(mTrisShader->Id());

        BINDVERTEXARRAY(arrayID);

        //Draw Triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Unbind Vertex Array Object and Shader
        BINDVERTEXARRAY(0);
        glUseProgram(0);
    }

    TriangleBuffer::~TriangleBuffer()
    {
        delete mTrisShader;
    }
}
