#ifndef L_ENGINE_NODE_H
#define L_ENGINE_NODE_H

#include <string>

#include "NodeType.h"

namespace html {
    /// A base class for all nodes in the HTML tree.
    class Node {
    public:
        /// Disable copying, as Node is a polymorphic base class (would cause slicing).
        Node(const Node &) = delete;

        /// Default virtual destructor, to allow safe deletion through a base class pointer.
        virtual ~Node() = default;

        /// Default move constructor.
        Node(Node &&) = default;

        /// Copy assignment is disabled, as Node is a polymorphic base class (would cause slicing).
        Node &operator=(const Node &) = delete;

        /// Default move assignment operator.
        Node &operator=(Node &&) = default;

        /**
         * Get the type of this node (either Text or Element).
         * @return The type of this node (either Text or Element).
         */
        [[nodiscard]] const NodeType &getType() const {
            return type;
        }

        /**
         * Get the total number of child nodes that are of type ElementNode, recursively counting all descendants.
         * @return The total number of child nodes that are of type ElementNode, recursively counting all descendants.
         */
        [[nodiscard]] virtual int getTotalElementNodeChildrens() const;

        /**
         * Convert this node and its children to an HTML string representation, appending it to the given output string.
         * @param out The output string.
         * @param level The current indentation level (used for pretty-printing).
         */
        virtual void toHTML(std::string &out, int level) const;

    protected:
        /**
         * Construct a new Node object with the given type.
         * @param type The type of this node (either Text or Element).
         */
        explicit Node(NodeType type);

    private:
        /// The type of the node (either Text or Element).
        NodeType type;
    };
}

#endif
