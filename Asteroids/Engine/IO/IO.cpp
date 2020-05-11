#include "IO.h"

namespace Engine {
    void key_callback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mode*/) {
        InputState* inputState = (InputState*)glfwGetWindowUserPointer(window);
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        if (key && (action == GLFW_PRESS || action == GLFW_RELEASE)) {
            (*inputState).keys[key] = action == GLFW_PRESS;
        }
    }

    void mouse_callback(GLFWwindow* window, int button, int action, int /*modifier*/) {
        InputState* inputState = (InputState*)glfwGetWindowUserPointer(window);
        if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
            (*inputState).CheckMouseMovement(window);
            (*inputState).clicks.push_back({ (*inputState).xpos, (*inputState).ypos });
        }
    }

    void character_callback(GLFWwindow* /*window*/, unsigned int /*codepoint*/) {

    }
}