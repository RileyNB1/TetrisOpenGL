#include <iostream>
#include <stdlib.h>

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>


int main()
{
    std::cout << "Hello World!\n";

    GLFWwindow* window;

    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(1024, 768, "GLFW", NULL, NULL);

    if (!window)
    {
        glfwTerminate();

        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    const GLubyte* p = glGetString(GL_VERSION);
    std::cout << "Open GL version = " << p << std::endl;
}