#pragma once

#include <OpenGLApp.h>

namespace FOGrP
{
    MVP OpenGLApp::mvp;

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
        keyCode = -1;
        eyePos = glm::vec3(0, 0, 5);
        forwardDir = glm::vec3(0, 0, -1); 
        
        mvp.view = glm::lookAt(eyePos, eyePos + forwardDir, glm::vec3(0, 1, 0));
        mvp.proj = glm::perspective(PI / 3.0f, mWindow.AspectRatio(), 0.1f, -10.0f);

        //mTris.Init(&mWindow);

        mCube.Init(&mWindow, MVP());

        //mesh.Init(&mWindow);

        //mTex.Init(&mWindow);

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
        //mTris.Draw();
        mCube.Draw();

        //mesh.Draw();

        //mTex.Draw();
    }

    void OpenGLApp::OnInput()
    {/*-----------------------------------------------------------------------------
     *  Every frame, check for keyboard input
     *-----------------------------------------------------------------------------*/
        if (keyCode != -1) {
            if (keyCode == GLFW_KEY_UP) eyePos += forwardDir * .01f;
            if (keyCode == GLFW_KEY_DOWN) eyePos -= forwardDir * .01f;
            if (keyCode == GLFW_KEY_LEFT) {
                glm::quat q = glm::angleAxis(.01f, glm::vec3(0, 1, 0));
                forwardDir = q * forwardDir;
            }
            if (keyCode == GLFW_KEY_RIGHT) {
                glm::quat q = glm::angleAxis(-.01f, glm::vec3(0, 1, 0));
                forwardDir = q * forwardDir;
            }
        }

        /*-----------------------------------------------------------------------------
         *  Set up view and projection matrices
         *-----------------------------------------------------------------------------*/
        mvp.view = glm::lookAt(eyePos, eyePos + forwardDir, glm::vec3(0, 1, 0));
        mvp.proj = glm::perspective(PI / 3.0f, mWindow.AspectRatio(), 0.1f, -10.0f);

        glUniformMatrix4fv(mvp.viewID, 1, GL_FALSE, glm::value_ptr(mvp.view));
        glUniformMatrix4fv(mvp.projectionID, 1, GL_FALSE, glm::value_ptr(mvp.proj));

    }

    void OpenGLApp::OnMouseMove(int x, int y)
    {
    }

    void OpenGLApp::OnMouseDown(int button, int action)
    {
    }

    void OpenGLApp::OnKeyDown(int key, int action)
    {
        if (action == GLFW_PRESS)
            keyCode = key;
        std::cout << "key pressed" << std::endl;
        if (action == GLFW_RELEASE) {
            keyCode = -1;
            std::cout << "key released" << std::endl;
        }
    }
}