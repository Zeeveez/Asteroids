#ifndef OPTIONS_H
#define OPTIONS_H

#include <vector>
#include "Engine/Text/Menu/Menu.h"

namespace Engine {
    class Options {
    public:
        typedef std::pair<int, int> ScreenSize;

    private:
        static std::vector<ScreenSize> screenSizes;

    public:
        static ScreenSize screenSize;
        static int volume;

        static Menu GetOptionsMenu();
        static void ChangeResolution(bool increase);
    };
}
#endif