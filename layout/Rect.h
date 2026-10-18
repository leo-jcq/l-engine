#ifndef L_ENGINE_RECT_H
#define L_ENGINE_RECT_H
#include "EdgeSizes.h"

namespace layout {
    /// A rectangle in 2D space, defined by its top-left corner (x, y) and its width and height.
    struct Rect {
        /// The x-coordinate of the top-left corner of the rectangle.
        float x;
        /// The y-coordinate of the top-left corner of the rectangle.
        float y;
        /// The width of the rectangle.
        float width;
        /// The height of the rectangle.
        float height;

        /**
         * Construct a new Rect object with all values set to 0.
         */
        Rect();

        /**
         * Construct a new Rect object with the given position and size.
         * @param x The x-coordinate of the top-left corner of the rectangle.
         * @param y The y-coordinate of the top-left corner of the rectangle.
         * @param width The width of the rectangle.
         * @param height The height of the rectangle.
         */
        Rect(float x, float y, float width, float height);

        /**
         * Creates a new Rect that is expanded by the given EdgeSizes.
         * @param edge The EdgeSizes to expand the rectangle by.
         * @return A new Rect that is expanded by the given EdgeSizes.
         */
        [[nodiscard]] Rect expandedBy(const EdgeSizes& edge) const {
            return {
                x - edge.left,
                y - edge.top,
                width + edge.left + edge.right,
                height + edge.top + edge.bottom
            };
        }
    };
}

#endif
