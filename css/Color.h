#ifndef L_ENGINE_COLOR_H
#define L_ENGINE_COLOR_H

#include <cstdint>

namespace css {
    /// An RGBA color value.
    struct Color {
        /// Red channel, in the range [0, 255].
        std::uint8_t r;
        /// Green channel, in the range [0, 255].
        std::uint8_t g;
        /// Blue channel, in the range [0, 255].
        std::uint8_t b;
        /// Alpha channel (opacity), in the range [0.0, 1.0]. Defaults to fully opaque.
        float a;

        /**
         * Construct a new Color object with the given RGBA values.
         * @param r Red channel, in the range [0, 255].
         * @param g Green channel, in the range [0, 255].
         * @param b Blue channel, in the range [0, 255].
         * @param a Alpha channel (opacity), in the range [0.0, 1.0]. Defaults to fully opaque.
         */
        Color(int r, int g, int b, float a);
    };
}

#endif
