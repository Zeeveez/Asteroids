#ifndef MENU_H
#define MENU_H

#include "Text/Text.h"
#include <vector>
#include <functional>

namespace Asteroids {
    class Menu {
    private:
        std::vector<std::pair<std::string, std::function<void()>>> options;
    public:
        Menu(std::vector<std::pair<std::string, std::function<void()>>> options);
        void Show(GLFWwindow* window);
    };
}

#endif
