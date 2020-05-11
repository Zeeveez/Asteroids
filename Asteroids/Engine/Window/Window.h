#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Engine {
    GLFWwindow* CreateGameWindow(int width, int height, const char* title, GLFWkeyfun keycallback, GLFWmousebuttonfun mousecallback, GLFWcharfun charactercallback);
}

#endif
