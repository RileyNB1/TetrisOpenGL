#include <GL_Lib.h>

namespace FOGrP
{
	/*-----------------------------------------------------------------------------
	*  Some Callbacks to be implemented later
	*-----------------------------------------------------------------------------*/
	struct MouseListener
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
}