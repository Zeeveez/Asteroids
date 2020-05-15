#ifndef MENU_H
#define MENU_H

#include "Engine/Text/Text.h"
#include <string>
#include <vector>
#include <functional>
#include <tuple>
#include <variant>

namespace Engine {
    class Menu;

    typedef std::tuple<std::string, std::variant<int*, std::function<void()>, Menu>> Option;
    class Menu {
    public:
        Menu(std::vector<Option> options, bool subMenu);
        void Show(GLFWwindow* window);

    private:
        std::vector<Option> options;
    };
}

#endif
