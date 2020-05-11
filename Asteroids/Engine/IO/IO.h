#ifndef IO_H
#define IO_H

#include <GLFW/glfw3.h>
#include <map>
#include <vector>

namespace Engine {
	struct InputState {
	public:
		double xpos;
		double ypos;
		double xdelta;
		double ydelta;
		char lastText;
		std::map<int, bool> keys;
		std::vector<std::pair<double,double>> clicks;
		void CheckMouseMovement(GLFWwindow* window) {
			pxpos = xpos;
			pypos = ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			xdelta = pxpos - xpos;
			ydelta = pypos - ypos;
		}
	private:
		double pxpos;
		double pypos;
	};

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void mouse_callback(GLFWwindow* window, int button, int action, int modifier);
	void character_callback(GLFWwindow* window, unsigned int codepoint);
}

#endif