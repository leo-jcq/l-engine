#include "Node.h"

#include <stdexcept>

namespace html {
    int Node::getTotalElementNodeChildrens() const {
        throw std::runtime_error("getTotalNodeChildrens() not implemented for base Node class");
    }

    void Node::toHTML(std::string &, const int) const {
        throw std::runtime_error("toHTML() not implemented for base Node class");
    }

    Node::Node(const NodeType type) : type(type) {
    }
}
