#ifndef L_ENGINE_STYLEDNODE_H
#define L_ENGINE_STYLEDNODE_H

#include <memory>
#include <optional>
#include <vector>

#include "Display.h"
#include "../css/Declaration.h"
#include "../dom/Node.h"

namespace style {
    /// A mapping of CSS property names to their values.
    using PropertyMap = std::unordered_map<std::string, css::Value>;

    /// A Node, with associated style data
    class StyledNode {
    public:
        StyledNode(const std::unique_ptr<dom::Node>& node, PropertyMap specifiedValues, std::vector<StyledNode> children);

        /**
         * Get the specified value of a property if it exists, otherwise @code std::nullopt@endcode.
         * @param name The name of the property.
         * @return The specified value of a property if it exists, otherwise @code std::nullopt@endcode.
         */
        [[nodiscard]] std::optional<css::Value> getValue(const std::string& name) const;

        /**
         * Get the value of a property, falling back to another property if not specified, and returning a default value if neither is specified.
         * @param name The name of the property to look up.
         * @param fallbackName The name of the property to fall back to if the first is not specified.
         * @param defaultVal The default value to return if neither property is specified.
         * @return The value of the property, falling back to another property if not specified, and returning a default value if neither is specified.
         */
        [[nodiscard]] css::Value lookup(const std::string& name, const std::string& fallbackName,
                                        const css::Value& defaultVal) const;

        /**
         * Get the value of the "display" property, defaulting to Display::Block if not specified or invalid.
         * @return The value of the "display" property.
         */
        [[nodiscard]] Display getDisplay() const;

    private:
        const std::unique_ptr<dom::Node>& node;
        PropertyMap specifiedValues;
        std::vector<StyledNode> children;
    };
}

#endif
