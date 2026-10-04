#include "TextNode.h"

namespace dom {
    TextNode::TextNode(std::string text) : Node(NodeType::Text), text(std::move(text)) {
    }

    int TextNode::getTotalElementNodeChildren() const {
        return 0;
    }

    void TextNode::toHTML(std::string &out, const int) const {
        out.append(text);
    }
}
