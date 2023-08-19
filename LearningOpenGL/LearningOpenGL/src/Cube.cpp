#pragma once

#include <Cube.h>

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

        mShader = new Shader();

        // With Shader bound, get attribute and uniform locations:

        // Get attribute locations
        positionID = mShader->GetUniformLocation("position");
        colorID = mShader->GetUniformLocation("color");
        textureCoordinateID = mShader->GetUniformLocation("textureCoordinate");

        // Get uniform locations
        modelID = mShader->GetUniformLocation("model");
        viewID = mShader->GetUniformLocation("view");
        projectionID = mShader->GetUniformLocation("projection");

        //****************/
        normalMatrixID = mShader->GetUniformLocation("normalMatrix");

        BindVertexData();
    }

    void FOGrP::Cube::BindVertexData()
    {
        Bitmap img("resources/flower.bmp");

        int tw = img.width;
        int th = img.height;




        //Specify the 8 VERTICES of A Cube
        //                  position          normal          color          texturecoord
        CubeVert cube[] = {
                         { glm::vec3(1, -1,  1), glm::vec3(1,-1, 1), glm::vec4(.5,.5,.5,1), glm::vec2(1,0) } ,
                         { glm::vec3(1,  1,  1), glm::vec3(1, 1, 1), glm::vec4(.5,.5,.5,1), glm::vec2(1,1) } ,
                         { glm::vec3(-1,  1,  1), glm::vec3(-1, 1, 1), glm::vec4(.5,.5,.5,1), glm::vec2(0,1) } ,
                         { glm::vec3(-1, -1,  1), glm::vec3(-1,-1, 1), glm::vec4(.5,.5,.5,1), glm::vec2(0,0) } ,

                         { glm::vec3(1, -1, -1), glm::vec3(1,-1,-1), glm::vec4(.5,.5,.5,1), glm::vec2(0,0) } ,
                         { glm::vec3(1,  1, -1), glm::vec3(1, 1,-1), glm::vec4(.5,.5,.5,1), glm::vec2(0,1) } ,
                         { glm::vec3(-1,  1, -1), glm::vec3(-1, 1,-1), glm::vec4(.5,.5,.5,1), glm::vec2(1,1) } ,
                         { glm::vec3(-1, -1, -1), glm::vec3(-1,-1,-1), glm::vec4(.5,.5,.5,1), glm::vec2(1,0) }
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
        glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(CubeVert), cube, GL_STATIC_DRAW);

        /*-----------------------------------------------------------------------------
        *  CREATE THE ELEMENT ARRAY BUFFER OBJECT
        *-----------------------------------------------------------------------------*/
        glGenBuffers(1, &elementID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24 * sizeof(CubeVert), indices, GL_STATIC_DRAW);

        /*-----------------------------------------------------------------------------
         *  ENABLE VERTEX ATTRIBUTES
         *-----------------------------------------------------------------------------*/
        glEnableVertexAttribArray(positionID);
        glEnableVertexAttribArray(colorID);
        glEnableVertexAttribArray(normalID);   //<-- Enable normalID attribute
        glEnableVertexAttribArray(textureCoordinateID);

        // Tell OpenGL how to handle the buffer of data that is already on the GPU
        glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(CubeVert), 0);
        
        glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(CubeVert),
            (void*)CubeVert::offsetColor());
        
        glVertexAttribPointer(normalID, 3, GL_FLOAT, GL_FALSE, sizeof(CubeVert),
            (void*)CubeVert::offsetNormal());
        
        glVertexAttribPointer(textureCoordinateID, 2, GL_FLOAT, GL_FALSE, sizeof(CubeVert),
            (void*)CubeVert::offsetTextureCoordinate());

        // Unbind Everything (NOTE: unbind the vertex array object first)
        BINDVERTEXARRAY(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        /*-----------------------------------------------------------------------------
        *  Generate Texture and Bind it
        *-----------------------------------------------------------------------------*/
        glGenTextures(1, &tID);
        glBindTexture(GL_TEXTURE_2D, tID);

        /*-----------------------------------------------------------------------------
         *  Allocate Memory on the GPU
         *-----------------------------------------------------------------------------*/
         // target | lod | internal_format | width | height | border | format | type | data
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tw, th, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        /*-----------------------------------------------------------------------------
         *  Load data onto GPU
         *-----------------------------------------------------------------------------*/
         // target | lod | xoffset | yoffset | width | height | format | type | data
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, tw, th, GL_BGR, GL_UNSIGNED_BYTE, img.pixels.data());
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        /*-----------------------------------------------------------------------------
         *  Unbind texture
         *-----------------------------------------------------------------------------*/
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void FOGrP::Cube::Draw()
    {
        static float time = 0.0;
        time += .01;

        glUseProgram(mShader->Id());
        glBindTexture(GL_TEXTURE_2D, tID);
        BINDVERTEXARRAY(arrayID);

        glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
       
        glm::mat4 proj = glm::perspective(3.14f / 3.0f, mWindow->AspectRatio(), 0.1f, -10.0f);
        
        glm::mat4 model = glm::rotate(glm::mat4(1), time, glm::vec3(0, 1, 0));
        
        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(view * model)));

        glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(proj));
        glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, (void*)0);

        BINDVERTEXARRAY(0);
        glUseProgram(0);
    }

    FOGrP::Cube::~Cube()
    {
    }
}
