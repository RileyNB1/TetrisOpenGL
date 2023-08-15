#include <Window.h>

namespace FOGrP
{
	//void* MouseListener::app;

	Window::Window()
	{
		mWidth = 0;
		mHeight = 0;
	}

	//template<class APPLICATION>
	void Window::Create(/*APPLICATION* app, */int w, int h, const char* name)
	{
		//interface.app = app;

		mWidth = w; mHeight = h;

		window = glfwCreateWindow(mWidth, mHeight, name, NULL, NULL);
		
		if (!window)
		{
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwMakeContextCurrent(window);
		glfwSwapInterval(1); //<-- force interval (not guaranteed to work with all graphics drivers)

		//register callbacks for keyboard and mouse
		/*glfwSetKeyCallback(window, MouseListener::OnKeyDown<APPLICATION>);
		glfwSetCursorPosCallback(window, MouseListener::OnMouseMove<APPLICATION>);
		glfwSetMouseButtonCallback(window, MouseListener::OnMouseDown<APPLICATION>);*/

	}

	void Window::SetViewport()
	{
		glfwGetFramebufferSize(window, &mWidth, &mHeight);
		glViewport(0, 0, mWidth, mHeight);
	}

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(window);

	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}

	void Window::Destroy()
	{
		glfwDestroyWindow(window);
	}

	Window::~Window()
	{
		Destroy();
	}

	int Window::Width() const
	{
		return mWidth;
	}

	int Window::Height() const
	{
		return mHeight;
	}

	float Window::AspectRatio() const
	{
		return mWidth / mHeight;
	}
}