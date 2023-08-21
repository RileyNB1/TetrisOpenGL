#pragma once

#include <Window.h>
#include <BaseApp.h>

namespace FOGrP
{
	Window::Window()
	{
		mWidth = 0;
		mHeight = 0;
	}

	void Window::Create(int w, int h, const char* name)
	{

		mWidth = w; mHeight = h;

		window = glfwCreateWindow(mWidth, mHeight, name, NULL, NULL);
		
		if (!window)
		{
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwMakeContextCurrent(window);
		glfwSwapInterval(1); //<-- force interval (not guaranteed to work with all graphics drivers)

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
		return (float)mWidth / mHeight;
	}

	GLFWwindow* Window::GetGLFWWindow()
	{
		return window;
	}
}