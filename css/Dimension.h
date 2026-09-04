#ifndef L_ENGINE_DIMENSION_H
#define L_ENGINE_DIMENSION_H

#include "Unit.h"

namespace css {
    /// Represent a numeric value of a CSS declaration
    struct Dimension {
        /// The value
        float value;
        /// The unit of the value
        Unit unit;

        /**
         * Construct a new Dimension object
         * @param value The value
         * @param unit The unit
         */
        Dimension(float value, Unit unit);
    };
}

#endif
