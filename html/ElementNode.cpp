#include "ElementNode.h"

namespace html {
    ElementNode::ElementNode(std::string tagName, AttrMap attrs,
                             std::vector<std::unique_ptr<Node> > children) : Node(NodeType::Element),
                                                                             tagName(std::move(tagName)),
                                                                             attrs(std::move(attrs)),
                                                                             children(std::move(children)) {
    }

    std::optional<std::string> ElementNode::getAttribute(const std::string &name) const {
        const auto it = attrs.find(name);

        if (it == attrs.end()) {
            return std::nullopt;
        }

        return it->second;
    }
}
