// Asteroids.cpp : Defines the entry point for the application.
//

#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Other includes
#include "AsteroidsGame/AsteroidsGame.h"
#include "Engine/IO/IO.h"
#include "Engine/Window/Window.h"
#include "Engine/Timing/Timing.h"
#include "Engine/Texture/Texture.h"
#include "Engine/HUD/HUDElement/Text/Text.h"
#include "Engine/HUD/HUDElement/Text/Menu/Menu.h"
#include "Engine/HUD/HUDElement/ProgressBar/ProgressBar.h"
#include "Engine/Audio/Audio.h"
#include "Engine/Options/Options.h"
#include <string>

void Game(GLFWwindow* window);

int main() {
    glfwInit();
    Engine::Audio::LoadDeviceAndContext();
    GLFWwindow* window = Engine::CreateGameWindow(Engine::Options::screenSize.first, Engine::Options::screenSize.second, "OpenGL", Engine::key_callback, Engine::mouse_callback, Engine::character_callback);
    Engine::Options::LoadConfig();
    Engine::Menu menu(
        {
            { "New Game", [window]() { Game(window); } },
            { "Options", Engine::Options::GetOptionsMenu() },
            { "Quit", [window]() { glfwSetWindowShouldClose(window, true); } }
        }, false);
    while (!glfwWindowShouldClose(window)) {
        menu.Show(window);
    }
    glfwTerminate();
    Engine::Audio::UnloadDeviceAndContext();
    return 0;
}

void Game(GLFWwindow* window) {
    Engine::InputState inputState = {};
    void* oldInputState = glfwGetWindowUserPointer(window);
    glfwSetWindowUserPointer(window, (void*)(&inputState));
    Asteroids::AsteroidsGame game(Engine::Options::screenSize.first, Engine::Options::screenSize.second);
    Engine::GameTimer timer(0.01666667f);
    Engine::Shader textShader("./text");
    Engine::Shader graphicsShader("./default");
    Engine::Texture font("./font.dds");
    timer.Start();
    int i = 0;

    float v = 0;
    float min = 0;
    float max = 120;
    Engine::ProgressBar progBar(&v, &min, &max);


    while (true) {
        v = (int)(v + 1) % (int)max;
        timer.Tick();
        while (timer.ConsumeTick() && !glfwWindowShouldClose(window)) {
            glfwPollEvents();
            game.HandleEvents(inputState);
            game.Update(inputState);
        }
        if (glfwWindowShouldClose(window)) {
            glfwSetWindowUserPointer(window, oldInputState);
            glfwSetWindowShouldClose(window, false);
            break;
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        game.DrawFrame();
        Engine::Text::DrawString(font, textShader, Engine::Text::Anchor::TOP_LEFT, -1.0f, 1.0f, 24, "Score: " + std::to_string(game.GetScore()) + "\nStage: " + std::to_string(game.GetStage()));
        progBar.Draw(graphicsShader, -0.5f, 0.9f, 1.0f, 0.1f, Engine::ProgressBar::Anchor::TOP_CENTER);
        glfwSwapBuffers(window);
    }
}