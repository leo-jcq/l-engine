#ifndef L_ENGINE_DIMENSIONS_H
#define L_ENGINE_DIMENSIONS_H

#include "EdgeSizes.h"
#include "Rect.h"

namespace layout {
    /// Represents the dimensions of a box, including content, padding, border, and margin.
    struct Dimensions {
        /// Position and size of the content.
        Rect content;

        /// Sizes of the padding
        EdgeSizes padding;
        /// Sizes of the border
        EdgeSizes border;
        /// Sizes of the margin
        EdgeSizes margin;

        /// Constructs a new Dimensions object with default values.
        Dimensions();

        /**
         * Constructs a new Dimensions object with the given content rectangle, padding, border, and margin.
         * @param content Position and size of the content.
         * @param padding Sizes of the padding.
         * @param border Sizes of the border.
         * @param margin Sizes of the margin.
         */
        Dimensions(Rect content, EdgeSizes padding, EdgeSizes border, EdgeSizes margin);
    };
}

#endif