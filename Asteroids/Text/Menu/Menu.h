#ifndef MENU_H
#define MENU_H

#include "Text/Text.h"
#include <string>
#include <vector>
#include <functional>
#include <tuple>

namespace Asteroids {
    class Menu {
    public:
        Menu(std::vector<std::tuple<std::function<std::string()>, std::function<void()>, std::function<void()>>> options);
        void Show(GLFWwindow* window);

    private:
        std::vector<std::tuple<std::function<std::string()>, std::function<void()>, std::function<void()>>> options;
    };
}

#endif
