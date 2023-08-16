#pragma once

#include <GL_Lib.h>
#include <iostream>

namespace FOGrP
{
    class Shader 
    {
        GLuint sID;

    public:

        GLuint Id() const;

        Shader();

        Shader(const char* vert, const char* frag);

        void Bind();

        void Unbind();

        /*-----------------------------------------------------------------------------
         *  FUNCION TO CHECK FOR SHADER COMPILER ERRORS
         *-----------------------------------------------------------------------------*/
        void CompilerCheck(GLuint ID);


        /*-----------------------------------------------------------------------------
         *  FUNCION TO CHECK FOR SHADER LINK ERRORS
         *-----------------------------------------------------------------------------*/
        void LinkCheck(GLuint ID);
    };
}