#ifndef L_ENGINE_DISPLAY_H
#define L_ENGINE_DISPLAY_H
#include <unordered_map>

namespace style {
    enum class Display {
        Inline,
        Block,
        None
    };

    inline const std::unordered_map<std::string, Display> DefaultDisplay = {
        {"span", Display::Inline}
    };
}

#endif
