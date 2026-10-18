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

        /**
         * Returns the rectangle representing the padding box, which is the content box expanded by the padding sizes.
         * @return The rectangle representing the padding box.
         */
        [[nodiscard]] Rect getPaddingBox() const {
            return content.expandedBy(padding);
        }

        /**
         * Returns the rectangle representing the border box, which is the padding box expanded by the border sizes.
         * @return The rectangle representing the border box.
         */
        [[nodiscard]] Rect getBorderBox() const {
            return getPaddingBox().expandedBy(border);
        }

        /**
         * Returns the rectangle representing the margin box, which is the border box expanded by the margin sizes.
         * @return The rectangle representing the margin box.
         */
        [[nodiscard]] Rect getMarginBox() const {
            return getBorderBox().expandedBy(margin);
        }
    };
}

#endif