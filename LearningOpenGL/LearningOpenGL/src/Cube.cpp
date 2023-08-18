#include <Cube.h>

/*-----------------------------------------------------------------------------
     *  SOME SHADER CODE
     *-----------------------------------------------------------------------------*/
//const char* vert = GLSL(120,
//
//attribute vec4 position;
//attribute vec4 color;
//
//varying vec4 dstColor;             //<-- new uniform matrix
//
//
//uniform mat4 model;
//uniform mat4 view;                                      //<-- 4x4 Transformation Matrices
//uniform mat4 projection;
//
//void main() {
//    dstColor = color;
//    gl_Position = projection * view * model * position;   //<-- Apply transformation 
//}
//
//);
//
//const char* frag = GLSL(120,
//
//    varying vec4 dstColor;
//
//void main() {
//    gl_FragColor = dstColor;
//}
//
//);

namespace FOGrP
{
    FOGrP::Cube::Cube()
    {
    }

    void FOGrP::Cube::Init(Window* window)
    {
        mWindow = window;

        /*-----------------------------------------------------------------------------
         *  CREATE THE SHADER
         *-----------------------------------------------------------------------------*/

        //mShader = new Shader(vert, frag);

        // With Shader bound, get attribute and uniform locations:

        // Get attribute locations
        positionID = glGetAttribLocation(mShader->Id(), "position");
        colorID = glGetAttribLocation(mShader->Id(), "color");

        // Get uniform locations
        modelID = glGetUniformLocation(mShader->Id(), "model");
        viewID = glGetUniformLocation(mShader->Id(), "view");
        projectionID = glGetUniformLocation(mShader->Id(), "projection");

        BindVertexData();
    }

    void FOGrP::Cube::BindVertexData()
    {
        Vertex cube[] = {
                            {glm::vec3(1, -1,  1), glm::vec4(1,0,0,1)},
                            {glm::vec3(1,  1,  1), glm::vec4(0,1,0,1)},
                            {glm::vec3(-1,  1,  1), glm::vec4(0,0,1,1)},
                            {glm::vec3(-1, -1,  1), glm::vec4(1,0,0,1)},

                            {glm::vec3(1, -1, -1), glm::vec4(0,1,0,1)},
                            {glm::vec3(1,  1, -1), glm::vec4(0,0,1,1)},
                            {glm::vec3(-1,  1, -1), glm::vec4(1,0,0,1)},
                            {glm::vec3(-1, -1, -1), glm::vec4(0,1,0,1)}
        };


        //6-------------/5
      //  .           // |
    //2--------------1   |
    //    .          |   |
    //    .          |   |
    //    .          |   |
    //    .          |   |
    //    7.......   |   /4
    //               | //
    //3--------------/0

        GLubyte indices[24] = {
                          0,1,2,3, //front
                          7,6,5,4, //back
                          3,2,6,7, //left
                          4,5,1,0, //right
                          1,5,6,2, //top
                          4,0,3,7 }; //bottom
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
        glBindBuffer(GL_ARRAY_BUFFER, bufferID);
        glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(Vertex), cube, GL_STATIC_DRAW);


        /*-----------------------------------------------------------------------------
        *  CREATE THE ELEMENT ARRAY BUFFER OBJECT
        *-----------------------------------------------------------------------------*/
        glGenBuffers(1, &elementID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24 * sizeof(GLubyte), indices, GL_STATIC_DRAW);


        /*-----------------------------------------------------------------------------
         *  ENABLE VERTEX ATTRIBUTES
         *-----------------------------------------------------------------------------*/
        glEnableVertexAttribArray(positionID);
        glEnableVertexAttribArray(colorID);

        // Tell OpenGL how to handle the buffer of data that is already on the GPU
        //                      attrib    num   type     normalize   stride     offset
        glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));

        // Unbind Everything (NOTE: unbind the vertex array object first)
        BINDVERTEXARRAY(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void FOGrP::Cube::Draw()
    {
        static float time = 0.0;
        time += .01;

        glUseProgram(mShader->Id());
        BINDVERTEXARRAY(arrayID);

        glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        glm::mat4 proj = glm::perspective(3.14f / 3.f, (float)mWindow->AspectRatio(), 0.1f, -10.f);

        glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(proj));

        model =  glm::rotate(glm::mat4(1), time, glm::vec3(0, 1, 0));
        glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));

        //glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, elementID);
        glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, 0);

        BINDVERTEXARRAY(0);
        glUseProgram(0);
    }

    FOGrP::Cube::~Cube()
    {
    }
}
