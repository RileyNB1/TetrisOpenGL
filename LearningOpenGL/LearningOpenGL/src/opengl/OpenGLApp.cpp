#pragma once

#include <OpenGLApp.h>

namespace FOGrP
{
    MVP OpenGLApp::mvp;
    Mouse OpenGLApp::mouse;
    Window OpenGLApp::mWindow;
    OpenGLApp* OpenGLApp::Instance;

    OpenGLApp::OpenGLApp(int width, int height)
    {
        Instance = this;

        if (!glfwInit())
        {
            exit(EXIT_FAILURE);
        }

        mWindow.Create( width, height, "GLFW");

        GLFWwindow* glWin = mWindow.GetGLFWWindow();


        glfwSetKeyCallback(glWin, OnKeyDown);
        glfwSetCursorPosCallback(glWin, OnMouseMove);
        glfwSetMouseButtonCallback(glWin, OnMouseDown);

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

    MVP& OpenGLApp::MVP()
    {
        return mvp;
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
        mvp.keyCode= -1;
        mvp.eyePos = glm::vec3(0, 0, 5);
        mvp.forwardDir = glm::vec3(0, 0, -1);
        
        mvp.view = glm::lookAt(mvp.eyePos, mvp.eyePos + mvp.forwardDir, glm::vec3(0, 1, 0));
        mvp.proj = glm::perspective(PI / 3.0f, mWindow.AspectRatio(), 0.1f, -10.0f);

        mesh = Mesh();
        mesh.Init(&mWindow, MVP());

        while (!mWindow.ShouldClose())
        {
            mWindow.SetViewport();

            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            OnInput();
            OnDraw();

            mWindow.SwapBuffers();

            glfwPollEvents();
        }
    }

    void OpenGLApp::OnDraw()
    {
        mesh.Draw(); 
    }

    void OpenGLApp::OnInput()
    {
        /*-----------------------------------------------------------------------------
        *  Every frame, check for keyboard input
        *-----------------------------------------------------------------------------*/
        if (mvp.keyCode != -1) 
        {
            if (mvp.keyCode == GLFW_KEY_UP) mvp.eyePos += mvp.forwardDir * .01f;
            if (mvp.keyCode == GLFW_KEY_DOWN) mvp.eyePos -= mvp.forwardDir * .01f;
            if (mvp.keyCode == GLFW_KEY_LEFT) {
                glm::quat q = glm::angleAxis(.01f, glm::vec3(0, 1, 0));
                mvp.forwardDir = q * mvp.forwardDir;
            }
            if (mvp.keyCode == GLFW_KEY_RIGHT) {
                glm::quat q = glm::angleAxis(-.01f, glm::vec3(0, 1, 0));
                mvp.forwardDir = q * mvp.forwardDir;
            }
        }

        /*-----------------------------------------------------------------------------
         *  Set up view and projection matrices
         *-----------------------------------------------------------------------------*/
        mvp.view = glm::lookAt(mvp.eyePos, mvp.eyePos + mvp.forwardDir, glm::vec3(0, 1, 0));
        mvp.proj = glm::perspective(PI / 3.0f, mWindow.AspectRatio(), 0.1f, -10.0f);

        glUniformMatrix4fv(mvp.viewID, 1, GL_FALSE, glm::value_ptr(mvp.view));
        glUniformMatrix4fv(mvp.projectionID, 1, GL_FALSE, glm::value_ptr(mvp.proj));

    }

    void OpenGLApp::OnKeyDown(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS)
            mvp.keyCode = key;
        std::cout << "key pressed" << std::endl;
        if (action == GLFW_RELEASE) {
            mvp.keyCode = -1;
            std::cout << "key released" << std::endl;
        }
    }

    void OpenGLApp::OnMouseMove(GLFWwindow* window, double x, double y)
    {
        mouse.x = x;
        mouse.y = y;

        if (mouse.isDown)
        {
            OnMouseDrag(x, y);
        }
    }

    void OpenGLApp::OnMouseDown(GLFWwindow* window, int button, int action, int mods)
    {
        if (action == GLFW_PRESS) {
            mouse.isDown = true;
            double x, y;
            glfwGetCursorPos(window, &x, &y);
            mouse.lastX = x;
            mouse.lastY = y;
            mouse.tmpRot = Instance->mesh.mRot;
        }
        else {
            mouse.isDown = false;
        }
    }

    void OpenGLApp::OnMouseDrag(int x, int y) 
    {
        mouse.dx = mouse.x - mouse.lastX;
        mouse.dy = mouse.y - mouse.lastY;

        float wx = (float)mouse.dx / mWindow.Width();
        float wy = (float)mouse.dy / mWindow.Height();

        glm::vec3 axis = glm::cross(glm::vec3(0, 0, 1), glm::vec3(wx, -wy, 0));
        glm::quat q = glm::angleAxis(glm::length(axis), glm::normalize(axis));
        Instance->mesh.mRot = q * mouse.tmpRot;
    }
}