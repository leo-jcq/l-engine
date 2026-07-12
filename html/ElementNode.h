#ifndef L_ENGINE_ELEMENTNODE_H
#define L_ENGINE_ELEMENTNODE_H

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "Node.h"

namespace html {
    /// A node representing an HTML element (e.g. <div>).
    class ElementNode : public Node {
    public:
        /**
         * Construct a new ElementNode object.
         * @param tagName The tag name of this element (e.g. "div").
         * @param attrs The attributes of the element as a name -> value map.
         * @param children The child nodes of the element.
         */
        ElementNode(std::string tagName, std::unordered_map<std::string, std::string> attrs,
                    std::vector<std::unique_ptr<Node> > children);

        /**
         *.
         * @return The tag name of this element (e.g. "div").
         */
        [[nodiscard]] const std::string &getTagName() const {
            return tagName;
        }

        /**
         * @return All attributes of this element as a name -> value map.
         */
        [[nodiscard]] const std::unordered_map<std::string, std::string> &getAttrs() const {
            return attrs;
        }

        /**
         * Look up a single attribute by name.
         * @param name The attribute name to look up.
         * @return The attribute value, or @code std::nullopt@endcode if it isn't present.
         */
        [[nodiscard]] std::optional<std::string> getAttribute(const std::string &name) const;

        /**
         * @return The child nodes of the element.
         */
        [[nodiscard]] const std::vector<std::unique_ptr<Node> > &getChildren() const {
            return children;
        }

    private:
        /// The tag name of the element (e.g. "div").
        std::string tagName;
        /// The attributes of the element as a name -> value map.
        std::unordered_map<std::string, std::string> attrs;
        /// The child nodes of the element.
        std::vector<std::unique_ptr<Node> > children;
    };
}

#endif
