#include <iostream>
#include <OpenGLApp.h>

#ifndef  GLSL
#define GLSL(version,A) "#version " #version "\n" #A
#endif // ! GLSL

const int WIDTH = 1024;
const int HEIGHT = 768;

const char* vert = GLSL(120,

    attribute vec4 position;
    void main()
{
    gl_Position = position;
}
);

const char* frag = GLSL(120,
    void main()
    {
    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
);


GLuint sid;

void MakeShader()
{
    //CREATE SHDER PROGRAM
    sid = glCreateProgram();

    GLuint vid = glCreateShader(GL_VERTEX_SHADER);
    GLuint fid = glCreateShader(GL_FRAGMENT_SHADER);

    //LOAD SOURCE
    glShaderSource(vid, 1, &vert, NULL);
    glShaderSource(fid, 1, &frag, NULL);

    //COMPILE
    glCompileShader(vid);
    glCompileShader(fid);

    //shaderCompilerCheck(vid);
    //shaderCompilerCheck(fid);

    glAttachShader(sid, vid);
    glAttachShader(sid, fid);

    glLinkProgram(sid);

    glUseProgram(sid);
}

void Draw()
{
    glBegin(GL_TRIANGLES);

    //Vertex 1
    glColor3f(1, 0, 0); 
    glVertex3f(-1, 0, 0);

    //Vertex 2
    glColor3f(0, 1, 0);
    glVertex3f(0, 1, 0);

    //Vertex 3
    glColor3f(0, 0, 1);
    glVertex3f(1, 0, 0);

    glEnd();
}


int main()
{
    FOGrP::OpenGLApp app;

    app.Start();

    return 0;
}