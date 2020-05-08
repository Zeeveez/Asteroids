// Asteroids.cpp : Defines the entry point for the application.
//

#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Other includes
#include "./AsteroidsGame/AsteroidsGame.h"
#include "./IO/IO.h"
#include "./Window/Window.h"
#include "./Timing/Timing.h"
#include "./Texture/Texture.h"
#include "./Text/Text.h"
#include "./Text/Menu/Menu.h"
#include "./Audio/Audio.h"
#include "./Audio/WAV/WAV.h"
#include <string>

void Game(GLFWwindow* window);

int main() {
    glfwInit();
    GLFWwindow* window = Asteroids::CreateGameWindow(1000, 1000, "OpenGL", Asteroids::key_callback, Asteroids::mouse_callback, Asteroids::character_callback);
    Asteroids::Audio::LoadDeviceAndContext();
    Asteroids::Menu menu(
        {
            { "New Game", [window]() { Game(window); } },
            { "Quit", [window]() { glfwSetWindowShouldClose(window, true); } }
        });
    while (!glfwWindowShouldClose(window)) {
        menu.Show(window);
    }
    glfwTerminate();
    Asteroids::Audio::UnloadDeviceAndContext();
    return 0;
}

void Game(GLFWwindow* window) {
    Asteroids::InputState inputState = {};
    glfwSetWindowUserPointer(window, (void*)(&inputState));
    Asteroids::AsteroidsGame game(10, 1000, 1000);
    Asteroids::GameTimer timer(0.01666667f);
    Asteroids::Shader textShader("./text");
    Asteroids::Texture font("./font.DDS");
    timer.Start();
    int i = 0;
    while (true) {
        timer.Tick();
        while (timer.ConsumeTick() && !glfwWindowShouldClose(window)) {
            glfwPollEvents();
            game.HandleEvents(inputState);
            game.Update(inputState);
        }
        if (glfwWindowShouldClose(window)) {
            glfwSetWindowShouldClose(window, false);
            break;
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        game.DrawFrame();
        Asteroids::DrawString(font, textShader, -1.0f, 0.925f, 0.075f, "Score: " + std::to_string(game.GetScore()));
        glfwSwapBuffers(window);
    }
}