#include <iostream>
#include <OpenGLApp.h>

#ifndef  GLSL
#define GLSL(version,A) "#version " #version "\n" #A
#endif // ! GLSL

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