#include "Menu.h"
#include "../../IO/IO.h"
#include "../../Timing/Timing.h"

namespace Asteroids {
    Menu::Menu(std::vector<std::pair<std::string, std::function<void()>>> options) : options(options) {}

    void Menu::Show(GLFWwindow* window) {
        Asteroids::InputState inputState = {};
        glfwSetWindowUserPointer(window, (void*)(&inputState));
        Asteroids::GameTimer timer(0.01666667f);
        Asteroids::Shader textShader("./text");
        Asteroids::Texture font("./font.DDS");

        int selection = 0;
        while (true) {
            timer.Tick();
            while (timer.ConsumeTick() && !glfwWindowShouldClose(window)) {
                glfwPollEvents();
                if (inputState.keys[GLFW_KEY_W]) {
                    selection = (selection + options.size() - 1) % options.size();
                    inputState.keys[GLFW_KEY_W] = false;
                    inputState.keys[GLFW_KEY_S] = false;
                }
                if (inputState.keys[GLFW_KEY_S]) {
                    selection = (selection + 1) % options.size();
                    inputState.keys[GLFW_KEY_W] = false;
                    inputState.keys[GLFW_KEY_S] = false;
                }
                if (inputState.keys[GLFW_KEY_SPACE]) {
                    options[selection].second();
                    return;
                }
            }
            if (glfwWindowShouldClose(window)) { break; }

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            for (int i = 0; i < options.size(); i++) {
                float y = 0.05f * (options.size() - 1) - 0.1f * i;
                Asteroids::DrawString(font, textShader, -0.375f, y, 0.125f,
                    (selection == i ? "> " : "  ") + options[i].first);
            }
            glfwSwapBuffers(window);
        }
    }
}