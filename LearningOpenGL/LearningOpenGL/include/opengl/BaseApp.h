#pragma once

#include <MouseListener.h>

namespace FOGrP
{
	class BaseApp : public MouseListener
	{
	public:
		virtual void OnKeyDown(GLFWwindow* window, int key, int scancode, int action, int mods) override;

		virtual void OnMouseMove(GLFWwindow* window, double x, double y) override;

		virtual void OnMouseDown(GLFWwindow* window, int button, int action, int mods) override;
	};
}

