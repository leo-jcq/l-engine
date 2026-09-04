#include "TextNode.h"

namespace html {
    TextNode::TextNode(std::string text) : Node(NodeType::Text), text(std::move(text)) {
    }
}