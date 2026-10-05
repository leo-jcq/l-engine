#include "LayoutBox.h"

namespace layout {
    LayoutBox::LayoutBox() : dimensions(Dimensions()),
                             type(BoxType::AnonymousBlock),
                             styleNode(std::nullopt) {
    }

    LayoutBox::LayoutBox(BoxType type, const style::StyledNode& styleNode) : dimensions(Dimensions()),
                                                                             type(std::move(type)),
                                                                             styleNode(std::make_optional(styleNode)) {
    }

    LayoutBox& LayoutBox::getInlineContainer() {
        if (type != BoxType::BlockNode) return *this;

        // If we've just generated an anonymous block box, keep using it
        if (children.size() > 0) {
            if (LayoutBox& last = children[children.size() - 1]; last.type == BoxType::AnonymousBlock) {
                return last;
            }
        }

        // Otherwise, create a new one
        LayoutBox anonymous{};
        children.push_back(anonymous);
        return anonymous;
    }
}
