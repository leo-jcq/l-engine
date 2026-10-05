#ifndef L_ENGINE_BUILD_H
#define L_ENGINE_BUILD_H

#include "LayoutBox.h"
#include "style/StyledNode.h"

namespace layout {
    /**
     * Builds a layout tree from a styled node without performing any layout calculations.
     * @param styleNode The styled node to build the layout tree from.
     * @return The root of the layout tree.
     */
    LayoutBox buildLayoutTree(const style::StyledNode& styleNode);
}

#endif
