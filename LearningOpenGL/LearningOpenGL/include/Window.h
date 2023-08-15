#pragma once

#include <MouseListener.h>

namespace FOGrP
{
	class Window
	{
        GLFWwindow* window;
        MouseListener interface;

        int mWidth, mHeight;

    public:

        Window();

        //Create a Window Context
        template<class APPLICATION>
        void Create(APPLICATION* app, int w, int h, const char* name = "demo");

        int Width() const;
        int Height() const;
        float AspectRatio() const;


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
