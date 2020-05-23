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
        static int screenSizeIndex;

    public:
        static ScreenSize screenSize;
        static int volume;
        static bool drawBounds;

        static Menu GetOptionsMenu();
        static void ChangeResolution(int change);
    };
}
#endif