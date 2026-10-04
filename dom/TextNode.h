#ifndef L_ENGINE_TEXTNODE_H
#define L_ENGINE_TEXTNODE_H

#include <string>

#include "Node.h"

namespace dom {
    /// Represents a text node in the HTML document tree.
    class TextNode : public Node {
    public:
        /**
         * Construct a new TextNode object.
         * @param text The raw text content of this node.
         */
        explicit TextNode(std::string text);

        /**
         * Get the raw text content of this node.
         * @return The raw text content of this node.
         */
        [[nodiscard]] const std::string &getText() const {
            return text;
        }

        [[nodiscard]] int getTotalElementNodeChildren() const override;

        void toHTML(std::string &out, int level) const override;

    private:
        /// The raw text content of this node.
        std::string text;
    };
}

#endif
