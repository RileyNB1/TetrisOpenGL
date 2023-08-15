#include <OpenGLApp.h>

namespace FOGrP
{
    OpenGLApp::OpenGLApp(int width, int height)
    {
        if (!glfwInit())
        {
            exit(EXIT_FAILURE);
        }

        mWindow.Create(/*this, */width, height, "GLFW");

        // Init Glew **************************
        glewExperimental = true;
        GLenum glewerror = glewInit();

        if (glewerror != GLEW_OK)
        {
            std::cout << "Glew error : \n\n" << glewGetErrorString(glewerror);
        }
        // End glew Init **********************


        if (!GLEW_VERSION_2_1)
        {
            std::cout << "OpenGL 2.1 not supported\n";
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
    }

    Window& OpenGLApp::Window()
    {
        return mWindow;
    }

    OpenGLApp::~OpenGLApp()
    {
        glfwTerminate();
    }

    void OpenGLApp::Start()
    {
        while (!mWindow.ShouldClose())
        {
            mWindow.SetViewport();

            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


            OnDraw();

            mWindow.SwapBuffers();

            glfwPollEvents();
        }
    }

    void OpenGLApp::OnDraw()
    {
        Draw();
    }

    void OpenGLApp::OnMouseMove(int x, int y)
    {
    }

    void OpenGLApp::OnMouseDown(int button, int action)
    {
    }

    void OpenGLApp::OnKeyDown(int key, int action)
    {
    }
}