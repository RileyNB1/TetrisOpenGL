#include <iostream>
#include <stdlib.h>

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
    GLFWwindow* window;

    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    int width = WIDTH;
    int height = HEIGHT;
    window = glfwCreateWindow(width, height, "GLFW", NULL, NULL);

    if (!window)
    {
        glfwTerminate();

        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    // Init Glew **************************
    glewExperimental = true;
    GLenum glewerror = glewInit();

    if (glewerror != GLEW_OK)
    {
        std::cout << "Glew error : \n\n" << glewGetErrorString(glewerror);

        return 0;
    }
    // End glew Init **********************


    if (!GLEW_VERSION_2_1)
    {
        std::cout << "OpenGL 2.1 not supported\n";

        return 0;
    }

    const GLubyte* p = glGetString(GL_VERSION);
    std::cout << "Open GL version = " << p << std::endl;

    const GLubyte* q = glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::cout << "GLSL version = " << q << std::endl;

    if (GLEW_ARB_vertex_array_object)
    {
        std::cout << "genVertexArrays supported \n";
    }

    if (GLEW_APPLE_vertex_array_object)
    {
        std::cout << "genVertexArraysAPPLE supported \n";
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLineWidth(3);

    // Main Loop***************************
    
    while (!glfwWindowShouldClose(window))
    {
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        Draw();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "Terminated\n";

    // Main loop end **********************

    return 0;
}