#include "Window.h"

namespace Engine {
    GLFWwindow* CreateGameWindow(int width, int height, const char* title, GLFWkeyfun keycallback, GLFWmousebuttonfun mousecallback, GLFWcharfun charactercallback) {
        //	Initialize GLFW and setup window config
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_SAMPLES, 4);

        // Create a GLFWwindow
        GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window) {
            std::cout << "Could not initialize window.";
            std::cin.get();
            exit(1);
        }
        glfwMakeContextCurrent(window);

        // Set the required callback functions
        glfwSetKeyCallback(window, keycallback);
        glfwSetMouseButtonCallback(window, mousecallback);
        glfwSetCharCallback(window, charactercallback);

        // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
        glewExperimental = GL_TRUE;

        // Initialize GLEW
        glewInit();

        return window;
    }
}
