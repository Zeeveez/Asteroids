#include "Menu.h"
#include "IO/IO.h"
#include "Timing/Timing.h"
#include "Audio/Audio.h"
#include "Audio/WAV/WAV.h"

namespace Asteroids {
    Menu::Menu(std::vector<std::tuple<std::function<std::string()>, std::function<void()>, std::function<void()>>> options) : options(options) {}

    void Menu::Show(GLFWwindow* window) {
        Asteroids::InputState inputState = {};
        glfwSetWindowUserPointer(window, (void*)(&inputState));
        Asteroids::GameTimer timer(0.01666667f);
        Asteroids::Shader textShader("./text");
        Asteroids::Texture font("./font.DDS");
        Asteroids::Audio selectSound(Asteroids::WAV("./MenuSelect.wav"));

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
                if (std::get<2>(options[selection])) {
                    if (inputState.keys[GLFW_KEY_A]) {
                        std::get<1>(options[selection])();
                        inputState.keys[GLFW_KEY_A] = false;
                        selectSound.Play();
                    }
                    if (inputState.keys[GLFW_KEY_D]) {
                        std::get<2>(options[selection])();
                        inputState.keys[GLFW_KEY_D] = false;
                        selectSound.Play();
                    }
                } else {
                    if (inputState.keys[GLFW_KEY_SPACE]) {
                        std::get<1>(options[selection])();
                        return;
                    }
                }
            }
            if (glfwWindowShouldClose(window)) { break; }

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            for (int i = 0; i < options.size(); i++) {
                float y = 0.05f * (options.size() - 1) - 0.1f * i;
                Asteroids::DrawString(font, textShader, -0.375f, y, 0.125f,
                    (selection == i ? "> " : "  ") + std::get<0>(options[i])());
            }
            glfwSwapBuffers(window);
        }
    }
}