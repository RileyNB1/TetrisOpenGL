#include "Shader.h"

GLuint FOGrP::Shader::Id() const
{
    return sID;
}

FOGrP::Shader::Shader()
{
}

FOGrP::Shader::Shader(const char* vert, const char* frag)
{
    /*-----------------------------------------------------------------------------
    *  CREATE THE SHADER
    *-----------------------------------------------------------------------------*/

    //1. CREATE SHADER PROGRAM
    sID = glCreateProgram();
    GLuint vID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fID = glCreateShader(GL_FRAGMENT_SHADER);

    //2. LOAD SHADER SOURCE CODE
    glShaderSource(vID, 1, &vert, NULL); //<-- Last argument specifies length of source string
    glShaderSource(fID, 1, &frag, NULL);

    //3. COMPILE
    glCompileShader(vID);
    glCompileShader(fID);

    //4. CHECK FOR COMPILE ERRORS
    CompilerCheck(vID);
    CompilerCheck(fID);

    //5. ATTACH SHADERS TO PROGRAM
    glAttachShader(sID, vID);
    glAttachShader(sID, fID);

    //6. LINK PROGRAM
    glLinkProgram(sID);

    //7. CHECK FOR LINKING ERRORS
    LinkCheck(sID);

    //8. USE PROGRAM
    glUseProgram(sID);
}

void FOGrP::Shader::Bind()
{
    glUseProgram(sID);
}

void FOGrP::Shader::Unbind()
{
    glUseProgram(0);
}

void FOGrP::Shader::CompilerCheck(GLuint ID)
{
    GLint comp;
    glGetShaderiv(ID, GL_COMPILE_STATUS, &comp);

    if (comp == GL_FALSE)
    {
        std::cout << "Shader Compilation FAILED" << std::endl;
        GLchar messages[256];
        glGetShaderInfoLog(ID, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
    }
}

void FOGrP::Shader::LinkCheck(GLuint ID)
{
    GLint linkStatus, validateStatus;
    glGetProgramiv(ID, GL_LINK_STATUS, &linkStatus);


    if (linkStatus == GL_FALSE)
    {
        std::cout << "Shader Linking FAILED" << std::endl;
        GLchar messages[256];
        glGetProgramInfoLog(ID, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
    }

    glValidateProgram(ID);
    glGetProgramiv(ID, GL_VALIDATE_STATUS, &validateStatus);

    std::cout << "Link: " << linkStatus << "  Validate: " << validateStatus << std::endl;
    if (linkStatus == GL_FALSE)
    {
        std::cout << "Shader Validation FAILED" << std::endl;
        GLchar messages[256];
        glGetProgramInfoLog(ID, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
    }
}