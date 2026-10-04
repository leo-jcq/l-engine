#include "StyledNode.h"

namespace style {
    StyledNode::StyledNode(const std::unique_ptr<dom::Node>& node, PropertyMap specifiedValues,
                           std::vector<StyledNode> children) : node(node),
                                                               specifiedValues(std::move(specifiedValues)),
                                                               children(std::move(children)) {
    }

    std::optional<css::Value> StyledNode::getValue(const std::string& name) const {
        const auto& val = specifiedValues.find(name);

        return val == specifiedValues.end() ? std::nullopt : std::make_optional(val->second);
    }

    css::Value StyledNode::lookup(const std::string& name, const std::string& fallbackName,
                                  const css::Value& defaultVal) const {
        std::optional<css::Value> val = getValue(name);

        if (!val.has_value()) {
            val = getValue(fallbackName);
        }

        return val.has_value() ? val.value() : defaultVal;
    }

    Display StyledNode::getDisplay() const {
        std::optional<css::Value> val = getValue("display");

        if (!val.has_value() && std::holds_alternative<std::string>(val.value())) {
            const std::string& displayValue = std::get<std::string>(val.value());

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
