#ifndef L_ENGINE_UTILS_H
#define L_ENGINE_UTILS_H

#include "Declaration.h"

namespace css {
    /**
     * Converts a CSS value to pixels. If the value is a dimension with unit "px", it returns the numeric value. Otherwise, it returns 0.
     * @param value The CSS value to convert to pixels.
     * @return The pixel value of the CSS value.
     */
    float valueToPx(const Value& value);
}

#endif
