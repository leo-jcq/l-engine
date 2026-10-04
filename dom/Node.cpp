#include "Node.h"

#include <stdexcept>

namespace dom {
    int Node::getTotalElementNodeChildren() const {
        throw std::runtime_error("getTotalNodeChildren() not implemented for base Node class");
    }

    void Node::toHTML(std::string &, const int) const {
        throw std::runtime_error("toHTML() not implemented for base Node class");
    }

    Node::Node(const NodeType type) : type(type) {
    }
}
