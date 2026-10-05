#ifndef L_ENGINE_BOXTYPE_H
#define L_ENGINE_BOXTYPE_H

namespace layout {
    /// Represents the type of a box in the layout tree.
    enum class BoxType {
        /// A block-level box, typically used for elements that start on a new line.
        BlockNode,
        /// An inline-level box, typically used for elements that flow within a line of text.
        InlineNode,
        /// An anonymous box, used to group inline boxes when necessary.
        AnonymousBlock
    };
}

#endif
