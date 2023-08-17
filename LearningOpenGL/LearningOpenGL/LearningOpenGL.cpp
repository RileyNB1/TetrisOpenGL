#include <iostream>
#include <OpenGLApp.h>

#ifndef  GLSL
#define GLSL(version,A) "#version " #version "\n" #A
#endif // ! GLSL


int main()
{
    FOGrP::OpenGLApp app;

    app.Start();

    return 0;
}