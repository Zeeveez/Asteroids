#include "Menu.h"
#include "Engine/IO/IO.h"
#include "Engine/Timing/Timing.h"
#include "Engine/Audio/Audio.h"

namespace Engine {
    Menu::Menu(std::vector<MenuItem> options, bool subMenu) : options(options) {
        if (subMenu) {
            this->options.push_back({ "Back", std::monostate() });
        }
    }

    void Menu::Show(GLFWwindow* window) {
        InputState inputState = {};
        void* oldInputState = glfwGetWindowUserPointer(window);
        glfwSetWindowUserPointer(window, (void*)(&inputState));
        GameTimer timer(0.01666667f);
        Shader textShader("./text");
        Texture font("./font.dds");
        Audio selectSound("./MenuSelect.wav");

        int selection = 0;
        while (true) {
            timer.Tick();
            while (timer.ConsumeTick() && !glfwWindowShouldClose(window)) {
                glfwPollEvents();
                if (inputState.keys[GLFW_KEY_W]) {
                    selection = (selection + options.size() - 1) % options.size();
                    inputState.keys[GLFW_KEY_W] = false;
                    inputState.keys[GLFW_KEY_S] = false;
                    selectSound.Play();
                }
                if (inputState.keys[GLFW_KEY_S]) {
                    selection = (selection + 1) % options.size();
                    inputState.keys[GLFW_KEY_W] = false;
                    inputState.keys[GLFW_KEY_S] = false;
                    selectSound.Play();
                }
                if (inputState.keys[GLFW_KEY_SPACE] && std::holds_alternative<std::monostate>(std::get<1>(options[selection]))) {
                    glfwSetWindowUserPointer(window, oldInputState);
                    return;
                } else {
                    if (std::holds_alternative<int*>(std::get<1>(options[selection]))) {
                        int* var = std::get<int*>(std::get<1>(options[selection]));
                        if (inputState.keys[GLFW_KEY_A]) {
                            (*var)--;
                            inputState.keys[GLFW_KEY_A] = false;
                            selectSound.Play();
                        }
                        if (inputState.keys[GLFW_KEY_D]) {
                            (*var)++;
                            inputState.keys[GLFW_KEY_D] = false;
                            selectSound.Play();
                        }
                    } else {
                        if (inputState.keys[GLFW_KEY_SPACE]) {
                            inputState.keys[GLFW_KEY_SPACE] = false;
                            if (std::holds_alternative<Menu>(std::get<1>(options[selection]))) {
                                std::get<Menu>(std::get<1>(options[selection])).Show(window);
                            } else {
                                std::get<std::function<void()>>(std::get<1>(options[selection]))();
                            }
                        }
                    }
                }
                if (glfwWindowShouldClose(window)) {
                    glfwSetWindowUserPointer(window, oldInputState);
                    return;
                }
            }

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            for (int i = 0; i < options.size(); i++) {
                float y = 0.05f * (options.size() - 1) - 0.1f * i;
                DrawString(font, textShader, -0.375f, y, 0.125f,
                    (selection == i ? "> " : "  ") + std::get<0>(options[i]));
            }
            glfwSwapBuffers(window);
        }
    }
}