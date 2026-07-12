#include "TextNode.h"

namespace html {
    TextNode::TextNode(std::string text) : Node(Text), text(std::move(text)) {
    }
}