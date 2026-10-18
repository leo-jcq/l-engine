#include "StyledNode.h"

namespace style {
    StyledNode::StyledNode(const std::unique_ptr<dom::Node>& node, PropertyMap specifiedValues,
                           std::vector<StyledNode> children) : node(node),
                                                               specifiedValues(std::move(specifiedValues)),
                                                               children(std::move(children)) {
    }

    const css::Value* StyledNode::getValue(const std::string& name) const {
        const auto it = specifiedValues.find(name);
        return it == specifiedValues.end() ? nullptr : &it->second;
    }

    const css::Value& StyledNode::lookup(const std::string& name, const std::string& fallbackName,
                                         const css::Value& defaultVal) const {
        if (const css::Value* val = getValue(name)) {
            return *val;
        }
        if (const css::Value* fallback = getValue(fallbackName)) {
            return *fallback;
        }

        return defaultVal;
    }

    Display StyledNode::getDisplay() const {
        if (const css::Value* val = getValue("display"); val && std::holds_alternative<std::string>(*val)) {
            const auto& displayValue = std::get<std::string>(*val);

            if (displayValue == "inline") {
                return Display::Inline;
            }

            if (displayValue == "none") {
                return Display::None;
            }
        }

        return Display::Block;
    }
}
