#pragma once

#include <Macros.h>

namespace FOGrP
{
	class Window
	{
        GLFWwindow* window;

        int mWidth, mHeight;

    public:

        Window();

        //Create a Window Context
        void Create(int w, int h, const char* name = "demo");

        int Width() const;
        int Height() const;
        float AspectRatio() const;

        GLFWwindow* GetGLFWWindow();

        //Get the Current framebuffer Size in pixels and Set the Viewport to it    
        void SetViewport();

        //Check whether window should close
        bool ShouldClose();

        //Swap front and back buffers
        void SwapBuffers();

        //Destroy the window
        void Destroy();

		~Window();
	};

}
