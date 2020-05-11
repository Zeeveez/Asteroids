#ifndef MENU_H
#define MENU_H

#include "Engine/Text/Text.h"
#include <string>
#include <vector>
#include <functional>
#include <tuple>

namespace Engine {
    class Menu {
    public:
        Menu(std::vector<std::tuple<std::function<std::string()>, std::function<void()>, std::function<void()>>> options);
        void Show(GLFWwindow* window);

    private:
        std::vector<std::tuple<std::function<std::string()>, std::function<void()>, std::function<void()>>> options;
    };
}

#endif
