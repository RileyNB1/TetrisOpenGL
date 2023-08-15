#pragma once

#include <GL_Lib.h>

namespace FOGrP
{
	/*-----------------------------------------------------------------------------
	*  Some Callbacks to be implemented later
	*-----------------------------------------------------------------------------*/
	struct Interface
    {
		static void* app; // <-- an unknown application to be defined later

		template<class APPLICATION>
		static void OnKeyDown(GLFWwindow* window, int key, int scancode, int action, int mods) {
			((APPLICATION*)(app))->onKeyDown(key, action);
		}

		template<class APPLICATION>
		static void OnMouseMove(GLFWwindow* window, double x, double y) {
			((APPLICATION*)(app))->onMouseMove(x, y);
		}

		template<class APPLICATION>
		static void OnMouseDown(GLFWwindow* window, int button, int action, int mods) {
			((APPLICATION*)(app))->onMouseDown(button, action);
		}

	};

	class Window
	{
        GLFWwindow* window;
        Interface interface;

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
