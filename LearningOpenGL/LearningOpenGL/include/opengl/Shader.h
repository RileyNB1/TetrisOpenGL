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

        void Bind();

        void Unbind();

        GLuint GetUniformLocation(const char* locationName);

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