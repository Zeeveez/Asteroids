#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H

#include <functional>

namespace Engine {
    void PostProcess(std::function<void()> renderCall);
}

#endif