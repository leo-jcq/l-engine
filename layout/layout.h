#ifndef L_ENGINE_BUILD_H
#define L_ENGINE_BUILD_H

#include "LayoutBox.h"

namespace layout {
    /**
     * Builds a layout tree from a styled node and performs layout calculations based on the containing block dimensions.
     * @param node The styled node to build the layout tree from.
     * @param containingBlock The dimensions of the containing block used for layout calculations.
     * @return The root of the layout tree after performing layout calculations.
     */
    LayoutBox layoutTree(const style::StyledNode& node, Dimensions& containingBlock);

    /**
     * Builds a layout tree from a styled node without performing any layout calculations.
     * @param styleNode The styled node to build the layout tree from.
     * @return The root of the layout tree.
     */
    static LayoutBox buildLayoutTree(const style::StyledNode& styleNode);
}

#endif
