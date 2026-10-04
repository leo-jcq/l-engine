#include "ElementNode.h"

#include <algorithm>

namespace html {
    ElementNode::ElementNode(std::string tagName, AttrMap attrs,
                             std::vector<std::unique_ptr<Node> > childrens)
        : Node(NodeType::Element),
          tagName(std::move(tagName)),
          attrs(std::move(attrs)),
          childrens(std::move(childrens)) {
    }

    std::optional<std::string> ElementNode::getAttribute(const std::string &name) const {
        const auto it = attrs.find(name);

        if (it == attrs.end()) {
            return std::nullopt;
        }

        return it->second;
    }

    int ElementNode::getTotalElementNodeChildrens() const {
        int count = 0;

        for (const auto &child : childrens) {
            count +=  child->getTotalElementNodeChildrens();
            if (child->getType() == NodeType::Element) count++;
        }

        return count;
    }

    void ElementNode::toHTML(std::string &out, const int level) const {
        // Create prefix
        std::string prefix;

        for (int i = 0; i < level; ++i) {
            prefix.append("    ");
        }

        // Init html
        if (level > 0) out.append("\n");
        out.append(prefix).append("<").append(tagName);

        // Add attributes
        for (const auto &[attrKey, attrValue] : attrs) {
            out.append(" ").append(attrKey).append("=\"").append(attrValue).append("\"");
        }

        // Close tag
        out.append(">");

        // Content
        for (const auto &child : childrens) {
            child->toHTML(out, level + 1);
        }

        // Closing tag
        if (getTotalElementNodeChildrens() >= 1) out.append("\n").append(prefix);
        out.append("</").append(tagName).append(">");
    }
}
