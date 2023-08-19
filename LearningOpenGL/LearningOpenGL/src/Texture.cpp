#pragma once

#include <Texture.h>

namespace FOGrP
{
    FOGrP::Texture::Texture()
    {
    }

    void FOGrP::Texture::Init(Window* window)
    {
        mWindow = window;
        /*-----------------------------------------------------------------------------
         *  Make some rgba data (can also load a file here)
         *-----------------------------------------------------------------------------*/
        //img = Bitmap("resources/flower.bmp");
        tw = 40;
        th = 40;       

        /*-----------------------------------------------------------------------------
         *  Create Shader
         *-----------------------------------------------------------------------------*/
        //mShader = new Shader(vert, frag);

        /*-----------------------------------------------------------------------------
         *  Get Attribute Locations
         *-----------------------------------------------------------------------------*/
        positionID = glGetAttribLocation(mShader->Id(), "position");
        textureCoordinateID = glGetAttribLocation(mShader->Id(), "textureCoordinate");

        BindVertexData();
    }

    void FOGrP::Texture::BindVertexData()
    {
        Bitmap img = Bitmap("flower.bmp");
        tw = img.width;
        th = img.height;
        /*-----------------------------------------------------------------------------
         *  A slab is just a rectangle with texture coordinates
         *-----------------------------------------------------------------------------*/
         //                  position      texture coord
        TexVertex slab[] = {
                          {glm::vec2(-.5,-.5), glm::vec2(0,0)}, //bottom-left
                          {glm::vec2(-.5, .8), glm::vec2(0,1)}, //top-left
                          {glm::vec2(.8, .8),  glm::vec2(1,1)}, //top-right
                          {glm::vec2(.8,-.5),  glm::vec2(1,0)}  //bottom-right
        }; 
        
        std::vector<glm::vec4> data;

        bool checker = false;
        for (int i = 0; i < tw; ++i) {
            float tu = (float)i / tw;
            for (int j = 0; j < th; ++j) {
                float tv = (float)j / th;
                data.push_back(glm::vec4(tu, 0, tv, checker));
                checker = !checker;
            }
            checker = !checker;
        }
        
        //  samplerID = glGetUniformLocation( shader->id(), "texture" );               //<-- unnecessary if only using one texture           

         /*-----------------------------------------------------------------------------
          *  Generate And Bind Vertex Array Object
          *-----------------------------------------------------------------------------*/
        GENVERTEXARRAYS(1, &arrayID);
        BINDVERTEXARRAY(arrayID);

        /*-----------------------------------------------------------------------------
         *  Generate Vertex Buffer Object
         *-----------------------------------------------------------------------------*/
        glGenBuffers(1, &bufferID);
        glBindBuffer(GL_ARRAY_BUFFER, bufferID);
        glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(TexVertex), slab, GL_STATIC_DRAW);

        /*-----------------------------------------------------------------------------
         *  Enable Vertex Attributes and Point to them
         *-----------------------------------------------------------------------------*/
        glEnableVertexAttribArray(positionID);
        glEnableVertexAttribArray(textureCoordinateID);
        glVertexAttribPointer(positionID, 2, GL_FLOAT, GL_FALSE, sizeof(TexVertex), 0);

        glVertexAttribPointer(textureCoordinateID,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(TexVertex),
            (void*)sizeof(glm::vec2));

        /*-----------------------------------------------------------------------------
         *  Unbind Vertex Array Object and the Vertex Array Buffer
         *-----------------------------------------------------------------------------*/
        BINDVERTEXARRAY(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        /*-----------------------------------------------------------------------------
         *  Generate Texture and Bind it
         *-----------------------------------------------------------------------------*/
        glGenTextures(1, &tID);
        glBindTexture(GL_TEXTURE_2D, tID);

        /*-----------------------------------------------------------------------------
         *  Allocate Memory on the GPU
         *-----------------------------------------------------------------------------*/
         // target | lod | internal_format | width | height | border | format | type | data
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        /*-----------------------------------------------------------------------------
         *  Load data onto GPU
         *-----------------------------------------------------------------------------*/
         // target | lod | xoffset | yoffset | width | height | format | type | data
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, tw, th, GL_BGR, GL_UNSIGNED_BYTE, img.pixels.data());

        //Mipmaps are good -- the regenerate the texture at various scales
        // and are necessary to avoid black screen if texParameters below are not set
        glGenerateMipmap(GL_TEXTURE_2D);

        // Set these parameters to avoid a black screen
        // caused by improperly mipmapped textures
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        /*-----------------------------------------------------------------------------
         *  Unbind texture
         *-----------------------------------------------------------------------------*/
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void FOGrP::Texture::Draw()
    {
        glUseProgram(mShader->Id());          //<-- 1. Bind Shader
        glBindTexture(GL_TEXTURE_2D, tID);   //<-- 2. Bind Texture
        BINDVERTEXARRAY(arrayID);              //<-- 3. Bind VAO

        glDrawArrays(GL_QUADS, 0, 4);         //<-- 4. Draw the four slab vertices
        
        BINDVERTEXARRAY(0);                   //<-- 5. Unbind the VAO
        glBindTexture(GL_TEXTURE_2D, 0);      //<-- 6. Unbind the texture
        glUseProgram(0);                     //<-- 7. Unbind the shader
    }

    FOGrP::Texture::~Texture()
    {
    }
}
