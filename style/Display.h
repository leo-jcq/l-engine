#ifndef L_ENGINE_DISPLAY_H
#define L_ENGINE_DISPLAY_H
#include <unordered_map>

namespace style {
    /**
     * Enum class representing the display property of an element.
     */
    enum class Display {
        /**
         * The element is displayed as an inline element, meaning it does not start on a new line and only takes up as much width as necessary.
         */
        Inline,
        /**
         * The element is displayed as a block element, meaning it starts on a new line and takes up the full width available.
         */
        Block,
        /**
         * The element is not displayed at all.
         */
        None
    };

    /**
     * A map of default display values for different HTML elements.
     */
    inline const std::unordered_map<std::string, Display> DefaultDisplay = {
        {"span", Display::Inline}
    };
}

#endif
