#include <iostream>
#include <stdlib.h>

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

const int WIDTH = 1024;
const int HEIGHT = 768;


int main()
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(WIDTH, HEIGHT, "GLFW", NULL, NULL);

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

    // Main Loop***************************
    
    while (!glfwWindowShouldClose(window))
    {
        glViewport(0, 0, WIDTH, HEIGHT);

        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "Terminated\n";

    // Main loop end **********************

    return 0;
}