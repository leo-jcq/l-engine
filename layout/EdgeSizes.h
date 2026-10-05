#ifndef L_ENGINE_EDGESIZES_H
#define L_ENGINE_EDGESIZES_H

namespace layout {
    /// The sizes of the edges of a box, in pixels.
    struct EdgeSizes {
        /// The size of the top edge.
        float top;
        /// The size of the right edge.
        float right;
        /// The size of the bottom edge.
        float bottom;
        /// The size of the left edge.
        float left;

        /**
         * Construct a new EdgeSizes object with all edge sizes set to 0.
         */
        EdgeSizes();

        /**
         * Construct a new EdgeSizes object with the given edge sizes.
         * @param top The size of the top edge.
         * @param right The size of the right edge.
         * @param bottom The size of the bottom edge.
         * @param left The size of the left edge.
         */
        EdgeSizes(float top, float right, float bottom, float left);
    };
}

#endif
