#ifndef L_ENGINE_LAYOUTBOX_H
#define L_ENGINE_LAYOUTBOX_H

#include <vector>

#include "BoxType.h"
#include "Dimensions.h"
#include "../style/StyledNode.h"

namespace layout {
    /// Represents a box in the layout tree.
    class LayoutBox {
    public:
        /// Constructs a new anonymous box with default values.
        LayoutBox();

        /// Constructs a new box with the given type and style node.
        LayoutBox(BoxType type, const style::StyledNode& styleNode);

        /**
         * Adds a new child box to this box.
         * @param newChildren The child box to add.
         */
        void addChildren(const LayoutBox& newChildren) {
            children.push_back(newChildren);
        }

        /**
         * Retrieves an inline container to store a new inline child.
         * @return The inline container box.
         */
        [[nodiscard]] LayoutBox& getInlineContainer();

        void layout(const Dimensions& containingBlock);

    private:
        void layoutBlock(const Dimensions& containingBlock);

        void calculateBlockWidth(const Dimensions& containingBlock);

        void calculateBlockPosition(const Dimensions& containingBlock);

        void layoutBlockChildren();

        void calculateBlockHeight();

        [[nodiscard]] const style::StyledNode& getStyledNode() const {
            if (type == BoxType::AnonymousBlock) throw std::runtime_error("Anonymous block box has no style node");
            if (!styleNode.has_value()) throw std::runtime_error("This block has no style node");

            return styleNode.value();
        }

        /// The dimensions of the box, including content, padding, border, and margin.
        Dimensions dimensions;
        /// The type of the box (block, inline, or anonymous).
        BoxType type;
        /// The child boxes of this box.
        std::vector<LayoutBox> children;
        /// The associated style node, if any.
        std::optional<style::StyledNode> styleNode{};
    };
}

#endif
