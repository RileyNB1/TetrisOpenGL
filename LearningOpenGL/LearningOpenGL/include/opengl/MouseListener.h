#include <GL_Lib.h>

namespace FOGrP
{
	/*-----------------------------------------------------------------------------
	*  Some Callbacks to be implemented later
	*-----------------------------------------------------------------------------*/
	class MouseListener
	{
	public:

		virtual void OnKeyDown(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;

		virtual void OnMouseMove(GLFWwindow* window, double x, double y) = 0;

		virtual void OnMouseDown(GLFWwindow* window, int button, int action, int mods) = 0;
	};
}