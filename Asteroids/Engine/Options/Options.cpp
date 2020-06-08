#include "Options.h"
#include "Engine/Audio/Audio.h"
#include <GLFW/glfw3.h>
#include <nlohmann/json.hpp>

namespace Engine {
    std::vector<Options::ScreenSize> Options::screenSizes = {
            { 640, 360 },
            { 800, 600 },
            { 1024, 768 },
            { 1280, 720 },
            { 1280, 800 },
            { 1280, 1024 },
            { 1360, 768 },
            { 1366, 768 },
            { 1440, 900 },
            { 1536, 864 },
            { 1600, 900 },
            { 1680, 1050 },
            { 1920, 1080 },
            { 1920, 1200 },
            { 2048, 1152 },
            { 2560, 1080 },
            { 2560, 1440 },
            { 3440, 1440 },
            { 3840, 2160 },
    };

    int Options::screenSizeIndex = 12;
    Options::ScreenSize Options::screenSize = screenSizes[screenSizeIndex];
    int Options::volume = 5;
    int Options::minVolume = 0;
    int Options::maxVolume = 10;
    bool Options::drawBounds = false;
    bool Options::drawParticles = true;
    bool Options::fullscreen = false;

    Menu Options::GetOptionsMenu() {
        std::vector<Engine::MenuItem> menuItems = {};
        menuItems.push_back({ "Volume", std::tuple<int*, int*, int*>{ (&volume), (&minVolume), (&maxVolume) } });
        // TODO: Update to have a left/right selection for resolution instead of 2 buttons
        menuItems.push_back({ "Increase Res", []() { ChangeResolution(1); } });
        menuItems.push_back({ "Decrease Res", []() { ChangeResolution(-1); } });
        menuItems.push_back({ "Toggle Fullscreen", []() { ToggleFullscreen(); } });
        menuItems.push_back({ "Save Settings", []() { SaveConfig(); } });
        return Engine::Menu(menuItems, true);
    }

    void Options::ChangeResolution(int change) {
        screenSizeIndex += change;
        if (screenSizeIndex < 0) {
            screenSizeIndex++;
        }
        if (screenSizeIndex >= screenSizes.size()) {
            screenSizeIndex--;
        }
        screenSize = screenSizes[screenSizeIndex];
        glfwSetWindowSize(glfwGetCurrentContext(), screenSize.first, screenSize.second);
        glViewport(0, 0, screenSize.first, screenSize.second);
    }

    void Options::ToggleFullscreen() {
        fullscreen = !fullscreen;
        glfwSetWindowMonitor(glfwGetCurrentContext(), fullscreen ? glfwGetPrimaryMonitor() : NULL, 0, 0, screenSize.first, screenSize.second, GLFW_DONT_CARE);
    }

    void Options::SaveConfig() {
        nlohmann::json json;
        json["volume"] = volume;
        json["screenSizeIndex"] = screenSizeIndex;
        json["fullscreen"] = fullscreen;
        std::ofstream f("config");
        f << json;
        f.close();
    }

    void Options::LoadConfig() {
        nlohmann::json json;
        std::ifstream f("config");
        if (f.good()) {
            f >> json;
            f.close();
            volume = json["volume"];
            screenSizeIndex = json["screenSizeIndex"];
            fullscreen = json["fullscreen"];

            screenSize = screenSizes[screenSizeIndex];
            glfwSetWindowSize(glfwGetCurrentContext(), screenSize.first, screenSize.second);
            glViewport(0, 0, screenSize.first, screenSize.second);
            glfwSetWindowMonitor(glfwGetCurrentContext(), fullscreen ? glfwGetPrimaryMonitor() : NULL, 0, 0, screenSize.first, screenSize.second, GLFW_DONT_CARE);
        }
    }
}