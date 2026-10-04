#ifndef L_ENGINE_ELEMENTNODE_H
#define L_ENGINE_ELEMENTNODE_H

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Node.h"

namespace dom {
    /// A map of attribute names to values for an HTML element.
    using AttrMap = std::unordered_map<std::string, std::string>;

    /// A node representing an HTML element (e.g. "<div>").
    class ElementNode : public Node {
    public:
        /**
         * Construct a new ElementNode object.
         * @param tagName The tag name of this element (e.g. "div").
         * @param attrs The attributes of the element as a name -> value map.
         * @param children The child nodes of the element.
         */
        ElementNode(std::string tagName, AttrMap attrs, std::vector<std::unique_ptr<Node> > children);

        /**
         * Get the tag name of this element (e.g. "div").
         * @return The tag name of this element (e.g. "div").
         */
        [[nodiscard]] const std::string& getTagName() const {
            return tagName;
        }

        /**
         * Get the child nodes of this element.
         * @return The child nodes of this element.
         */
        [[nodiscard]] const std::vector<std::unique_ptr<Node> >& getChildren() const {
            return children;
        }

        /**
         * Get the id attribute of this element, if it exists.
         * @return The id attribute of this element, or @code std@endcode::nullopt if it does not exist.
         */
        [[nodiscard]] std::optional<std::string> getId() const;

        /**
         * Get the class attribute of this element as a set of class names.
         * @return The class attribute of this element as a set of class names, or an empty set if it does not exist.
         */
        [[nodiscard]] std::unordered_set<std::string> getClasses() const;

        [[nodiscard]] int getTotalElementNodeChildren() const override;

        void toHTML(std::string &out, int level) const override;

    private:
        /// The tag name of the element (e.g. "div").
        std::string tagName;
        /// The attributes of the element as a name -> value map.
        AttrMap attrs;
        /// The child nodes of the element.
        std::vector<std::unique_ptr<Node> > children;
    };
}

#endif
