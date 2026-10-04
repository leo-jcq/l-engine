#include "ElementNode.h"

#include <algorithm>

namespace dom {
    ElementNode::ElementNode(std::string tagName, AttrMap attrs,
                             std::vector<std::unique_ptr<Node> > children)
        : Node(NodeType::Element),
          tagName(std::move(tagName)),
          attrs(std::move(attrs)),
          children(std::move(children)) {
    }

    std::optional<std::string> ElementNode::getId() const {
        const auto& val = attrs.find("id");
        return val == attrs.end() ? std::nullopt : std::make_optional(val->second);
    }

    std::unordered_set<std::string> ElementNode::getClasses() const {
        const auto& val = attrs.find("class");
        std::unordered_set<std::string> classes;

        if (val != attrs.end()) {
            std::string classList = val->second;
            size_t start = 0;
            size_t end = classList.find(' ');

            while (end != std::string::npos) {
                classes.insert(classList.substr(start, end - start));
                start = end + 1;
                end = classList.find(' ', start);
            }

            classes.insert(classList.substr(start));
        }

        return classes;
    }

    int ElementNode::getTotalElementNodeChildren() const {
        int count = 0;

        for (const auto &child : children) {
            count +=  child->getTotalElementNodeChildren();
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
        for (const auto &child : children) {
            child->toHTML(out, level + 1);
        }

        // Closing tag
        if (getTotalElementNodeChildren() >= 1) out.append("\n").append(prefix);
        out.append("</").append(tagName).append(">");
    }
}
