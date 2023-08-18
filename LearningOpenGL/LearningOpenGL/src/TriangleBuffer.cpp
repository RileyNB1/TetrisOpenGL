#include <TriangleBuffer.h>

namespace FOGrP
{

    /*-----------------------------------------------------------------------------
     *  SOME SHADER CODE
     *-----------------------------------------------------------------------------*/
    const char* vert = GLSL(120,

    attribute vec4 position;
    attribute vec4 color;

    varying vec4 dstColor;             //<-- new uniform matrix


    uniform mat4 model;
    uniform mat4 view;                                      //<-- 4x4 Transformation Matrices
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
        mWindow = 0;
    }

    void FOGrP::TriangleBuffer::Init(Window* window)
    {
        mWindow = window;
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
        *  View Transform: Eye Position        Target             Up Direction
        *-----------------------------------------------------------------------------*/
        view = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        /*-----------------------------------------------------------------------------
         *  Projection Transform:  Field of View     Ratio                     Near   Far
         *-----------------------------------------------------------------------------*/
         // glm requires us to use floats!  use .f or else you'll get compiler errors
        proj = glm::perspective(PI / 3.0f, (float)mWindow->AspectRatio(), 0.1f, -10.0f);

        /*-----------------------------------------------------------------------------
         *  Send view and projection matrices to Shader Uniforms
         *-----------------------------------------------------------------------------*/
        glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(proj));

        /*-----------------------------------------------------------------------------
         *  CREATE THE SHADER
         *-----------------------------------------------------------------------------*/

         //1. CREATE SHADER PROGRAM
        mShader = new Shader(vert, frag);
    }

    void TriangleBuffer::BindVertexData()
    {
        positionID = glGetAttribLocation(mShader->Id(), "position");
        colorID = glGetAttribLocation(mShader->Id(), "color");

        // Get uniform locations
        modelID = glGetUniformLocation(mShader->Id(), "model");
        viewID = glGetUniformLocation(mShader->Id(), "view");
        projectionID = glGetUniformLocation(mShader->Id(), "projection");

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

        BINDVERTEXARRAY(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void TriangleBuffer::Draw()
    {
        static float time = 0.0;
        time += .01;
        //Bind Shader and Vertex Array Object
        glUseProgram(mShader->Id());

        BINDVERTEXARRAY(arrayID);

        for (int i = 0; i < 100; ++i) {

            /*-----------------------------------------------------------------------------
             *  Create transformation matrices
             *-----------------------------------------------------------------------------*/
            glm::mat4 translate = glm::translate(glm::mat4(1), glm::vec3(sin(time), 0, (float)i / 100));
            glm::mat4 rotate = glm::rotate(glm::mat4(1), time * PI * i / 100, glm::vec3(0, 0, 1));
            glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(1.0f - (float)i / 100));

            /*-----------------------------------------------------------------------------
             *  Scale, then Rotate, then Translate = translate * rotate * scale
             *-----------------------------------------------------------------------------*/
            model = translate * rotate * scale;

            glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        //Unbind Vertex Array Object and Shader
        BINDVERTEXARRAY(0);
        glUseProgram(0);
    }

    TriangleBuffer::~TriangleBuffer()
    {
        delete mShader;
    }
}
