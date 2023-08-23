#pragma once

#include <TextureBuffer.h>

namespace FOGrP
{
    TextureBuffer::TextureBuffer(int w, int h) : width(w), height(h)
    {
        Init();
    };

    void TextureBuffer::Init()
    {
        BindVertexData();
    }

    void TextureBuffer::BindVertexData()
    {

        glGenTextures(1, &tID);
        glBindTexture(GL_TEXTURE_2D, tID);

        /*-----------------------------------------------------------------------------
         *  Allocate Memory on the GPU
         *-----------------------------------------------------------------------------*/
         // target | lod | internal_format | width | height | border | format | type | data
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, NULL);

        /*-----------------------------------------------------------------------------
         *  Set Texture Parameters
         *-----------------------------------------------------------------------------*/
         // Set these parameters to avoid a black screen caused by improperly mipmapped textures
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  //<-- or GL_LINEAR;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  //<-- or GL_LINEAR;

        //optional . . .
        //
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        /*-----------------------------------------------------------------------------
         *  Unbind texture
         *-----------------------------------------------------------------------------*/
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void TextureBuffer::Update(void* data)
    {
        Bind();
        /*-----------------------------------------------------------------------------
         *  Load data onto GPU
         *-----------------------------------------------------------------------------*/
         // target | lod | xoffset | yoffset | width | height | format | type | data
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_FLOAT, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        Unbind();
    }

    void TextureBuffer::Bind()
    { 
        glBindTexture(GL_TEXTURE_2D, tID); 
    }
    void TextureBuffer::Unbind()
    { 
        glBindTexture(GL_TEXTURE_2D, 0); 
    }

    TextureBuffer::~TextureBuffer()
    {
    }
}
