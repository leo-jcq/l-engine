#include "layout.h"

layout::LayoutBox layout::buildLayoutTree(const style::StyledNode& styleNode) {
    // Create the root box
    const style::Display display = styleNode.getDisplay();
    BoxType type;

    if (display == style::Display::Block) type = BoxType::BlockNode;
    if (display == style::Display::Inline) type = BoxType::InlineNode;
    else throw std::runtime_error("Root node has display: none.");

    LayoutBox root(type, styleNode);

    // Create the descendant boxes
    for (const style::StyledNode& child : styleNode.getChildren()) {
        switch (child.getDisplay()) {
        case style::Display::Block:
            root.addChildren(buildLayoutTree(child));
            break;
        case style::Display::Inline:
            root.getInlineContainer().addChildren(buildLayoutTree(child));
            break;
        case style::Display::None:
            // Skip nodes with display: none
            break;
        }
    }

    return root;
}
