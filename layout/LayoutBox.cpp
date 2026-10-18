#include "LayoutBox.h"

#include <optional>

#include "../css/utils.h"

namespace layout {
    LayoutBox::LayoutBox() : dimensions(Dimensions()),
                             type(BoxType::AnonymousBlock),
                             styleNode(std::nullopt) {
    }

    LayoutBox::LayoutBox(const BoxType type, const style::StyledNode& styleNode) : dimensions(Dimensions()), type(type),
        styleNode(std::make_optional(styleNode)) {
    }

    void LayoutBox::layout(const Dimensions& containingBlock) {
        if (type == BoxType::BlockNode) layoutBlock(containingBlock);
        // TODO : inline and anonymous block
    }

    void LayoutBox::layoutBlock(const Dimensions& containingBlock) {
        calculateBlockWidth(containingBlock);
        calculateBlockPosition(containingBlock);
        layoutBlockChildren();
        calculateBlockHeight();
    }

    void LayoutBox::calculateBlockWidth(const Dimensions& containingBlock) {
        const style::StyledNode& style = getStyledNode();

        const std::string autoVal = "auto";

        // Width with "auto" as initial value
        const css::Value* widthPtr = style.getValue("width");
        css::Value width = widthPtr ? *widthPtr : css::Value(autoVal);
        const bool widthIsAuto = std::holds_alternative<std::string>(width) && std::get<std::string>(width) == autoVal;

        // Margin, border and padding with 0 as initial value
        const css::Value zero(css::Dimension(0, css::Unit::Px));

        css::Value marginLeft = style.lookup("margin-left", "margin", zero);
        bool marginLeftIsAuto = std::holds_alternative<std::string>(marginLeft) &&
            std::get<std::string>(marginLeft) == autoVal;
        css::Value marginRight = style.lookup("margin-right", "margin", zero);
        bool marginRightIsAuto = std::holds_alternative<std::string>(marginRight) &&
            std::get<std::string>(marginRight) == autoVal;

        css::Value borderLeft = style.lookup("border-left-width", "border-width", zero);
        css::Value borderRight = style.lookup("border-right-width", "border-width", zero);

        css::Value paddingLeft = style.lookup("padding-left", "padding", zero);
        css::Value paddingRight = style.lookup("padding-right", "padding", zero);

        float total = css::valueToPx(marginLeft) + css::valueToPx(marginRight) + css::valueToPx(borderLeft) +
            css::valueToPx(borderRight) + css::valueToPx(paddingLeft) + css::valueToPx(paddingLeft);

        // If width is not auto and the total is wider than the container, treat auto margins as 0
        if (!widthIsAuto && total > containingBlock.content.width) {
            if (std::holds_alternative<std::string>(marginLeft) && std::get<std::string>(marginLeft) == autoVal) {
                marginLeft = zero;
                marginLeftIsAuto = false;
            }

            if (std::holds_alternative<std::string>(marginRight) && std::get<std::string>(marginRight) == autoVal) {
                marginRight = zero;
                marginRightIsAuto = false;
            }
        }

        // Adjust used values so that the above sum equals the containing block width
        const float underflow = containingBlock.content.width - total;

        // If width is set to auto, any other auto values become 0
        if (widthIsAuto) {
            if (marginLeftIsAuto) {
                marginLeft = css::Value(css::Dimension(0, css::Unit::Px));
            }

            if (marginRightIsAuto) {
                marginRight = css::Value(css::Dimension(0, css::Unit::Px));
            }

            if (underflow >= 0) {
                // Expand width to fill the underflow
                width = css::Value(css::Dimension(underflow, css::Unit::Px));
            } else {
                // Width can't be negative : adjust the right margin
                width = css::Value(css::Dimension(0, css::Unit::Px));
                marginRight = css::Value(css::Dimension(css::valueToPx(marginRight) + underflow, css::Unit::Px));
            }
        } else if (marginLeftIsAuto && marginRightIsAuto) {
            // If both margins are auto, their used values are equal
            marginLeft = css::Value(css::Dimension(underflow / 2, css::Unit::Px));
            marginRight = css::Value(css::Dimension(underflow / 2, css::Unit::Px));
        } else if (marginLeftIsAuto) {
            // If left margin left or right margin is auto, its used value follows from the equality.
            marginLeft = css::Value(css::Dimension(underflow, css::Unit::Px));
        } else if (marginRightIsAuto) {
            marginRight = css::Value(css::Dimension(underflow, css::Unit::Px));
        }

        // Apply values
        dimensions.content.width = css::valueToPx(width);

        dimensions.padding.left = css::valueToPx(paddingLeft);
        dimensions.padding.right = css::valueToPx(paddingRight);

        dimensions.border.left = css::valueToPx(borderLeft);
        dimensions.border.right = css::valueToPx(borderRight);

        dimensions.margin.left = css::valueToPx(marginLeft);
        dimensions.margin.right = css::valueToPx(marginRight);
    }

    void LayoutBox::calculateBlockPosition(const Dimensions& containingBlock) {
        const style::StyledNode& style = getStyledNode();

        // Margin, border and padding with 0 as initial value
        const css::Value zero(css::Dimension(0, css::Unit::Px));

        dimensions.margin.top = css::valueToPx(style.lookup("margin-top", "margin", zero));
        dimensions.margin.bottom = css::valueToPx(style.lookup("margin-bottom", "margin", zero));

        dimensions.border.top = css::valueToPx(style.lookup("border-top", "border", zero));
        dimensions.border.bottom = css::valueToPx(style.lookup("border-bottom", "border", zero));

        dimensions.padding.top = css::valueToPx(style.lookup("padding-top", "padding", zero));
        dimensions.padding.bottom = css::valueToPx(style.lookup("padding-bottom", "padding", zero));

        // Calculate position
        dimensions.content.x = containingBlock.content.x + dimensions.margin.left + dimensions.border.left + dimensions.
            padding.left;

        // Position the box below all the previous boxes in the container
        dimensions.content.y = containingBlock.content.height + containingBlock.content.y + dimensions.margin.top +
            dimensions.border.top + dimensions.padding.top;
    }

    void LayoutBox::layoutBlockChildren() {
        for (LayoutBox& child : children) {
            child.layout(dimensions);
            dimensions.content.height += child.dimensions.getMarginBox().height;
        }
    }

    void LayoutBox::calculateBlockHeight() {
        if (const css::Value* heightPtr = getStyledNode().getValue("height");
            heightPtr && std::holds_alternative<css::Dimension>(*heightPtr)) {
            // Only take pixel values for now
            if (const auto heightValue = std::get<css::Dimension>(*heightPtr); heightValue.unit == css::Unit::Px) {
                dimensions.content.height = heightValue.value;
            }
        }
    }

    LayoutBox& LayoutBox::getInlineContainer() {
        if (type != BoxType::BlockNode) return *this;

        // If we've just generated an anonymous block box, keep using it
        if (!children.empty()) {
            if (LayoutBox& last = children.back(); last.type == BoxType::AnonymousBlock) {
                return last;
            }
        }

        // Otherwise, create a new one
        children.emplace_back();
        return children.back();
    }
}
