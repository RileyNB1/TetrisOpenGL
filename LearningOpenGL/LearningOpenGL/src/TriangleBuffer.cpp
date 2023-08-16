#include "TriangleBuffer.h"

namespace FOGrP
{
    /*-----------------------------------------------------------------------------
     *  SOME SHADER CODE
     *-----------------------------------------------------------------------------*/
    const char* vert = GLSL(120,

        attribute vec4 position;
    attribute vec4 color;

    varying vec4 dstColor;

    uniform mat4 model;
    uniform mat4 view;                 //<-- 4x4 Transformation Matrices
    uniform mat4 projection;

    void main() {
        dstColor = color;
        gl_Position = projection * view * model * position;   //<-- Apply transformation 
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

        v1.position = glm::vec2(-1, 0);
        v1.color = glm::vec4(1, 0, 0, 1);

        v2.position = glm::vec2(0, 1);
        v2.color = glm::vec4(0, 1, 0, 1);

        v3.position = glm::vec2(1, 0);
        v3.color = glm::vec4(0, 0, 1, 1);

        //Specify the 3 VERTICES of A Triangle
        mTris[0] = v1;
        mTris[1] = v2;
        mTris[2] = v3;

        /*-----------------------------------------------------------------------------
         *  CREATE THE SHADER
         *-----------------------------------------------------------------------------*/

         //1. CREATE SHADER PROGRAM
        mTrisShader = new Shader(vert, frag);
    }

    void TriangleBuffer::BindVertexData()
    {
        // Get attribute locations
        positionID = glGetAttribLocation(mTrisShader->Id(), "position");
        colorID = glGetAttribLocation(mTrisShader->Id(), "color");

        // Get uniform locations
        modelID = glGetUniformLocation(mTrisShader->Id(), "model");
        viewID = glGetUniformLocation(mTrisShader->Id(), "view");
        projectionID = glGetUniformLocation(mTrisShader->Id(), "projection");

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
        glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vertex), &(mTris[0]), GL_STATIC_DRAW);


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

        //now we can unbind vertex array object and vertex buffer object
        BINDVERTEXARRAY(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void TriangleBuffer::Draw(const Window& window)
    {
        static float time = 0.0;
        time += .01;

        //Bind Shader and Vertex Array Object
        glUseProgram(mTrisShader->Id());
        BINDVERTEXARRAY(arrayID);

        /*-----------------------------------------------------------------------------
         *  Set up view and projection matrices
         *-----------------------------------------------------------------------------*/
        glm::vec3 eyepos = glm::vec3(cos(time) * 1.0, 0, sin(time) * 5.0);

        glm::mat4 view = glm::lookAt(eyepos,                           //eye
            glm::vec3(0, 0, 0),                 //target
            glm::vec3(0, 1, 0));               //up

        glm::mat4 proj = glm::perspective(PI / 3.0f, (float)window.AspectRatio(), 0.1f, -10.0f);

        glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(proj));

        /*-----------------------------------------------------------------------------
         *  Render a whole bunch of spinning triangles
         *-----------------------------------------------------------------------------*/
        int len = 10; int total = len * len * len;
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < len; ++j) {
                for (int k = 0; k < len; ++k) {
                    int idx = i * len * len + j * len + k;

                    glm::vec3 trs(-len / 2.0 + i, -len / 2.0 + j, -len / 2.0 + k);
                    glm::vec3 axis(0, 0, 1);
                    float rad = time * PI;
                    glm::vec3 vscale(1.0 - (float)idx / total);

                    glm::mat4 translation = glm::translate(glm::mat4(), trs);
                    glm::mat4 rotation = glm::rotate(glm::mat4(), rad, axis);
                    glm::mat4 scale = glm::scale(glm::mat4(), vscale);

                    //ORDER MATTERS!
                    glm::mat4 model = translation * rotation * scale;

                    glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));
                    glDrawArrays(GL_TRIANGLES, 0, 3);
                }
            }
        }

        //Unbind 
        BINDVERTEXARRAY(0);
        glUseProgram(0);
    }

    TriangleBuffer::~TriangleBuffer()
    {
        delete mTrisShader;
    }
}
