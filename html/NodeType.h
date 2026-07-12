#ifndef L_ENGINE_NODETYPE_H
#define L_ENGINE_NODETYPE_H

namespace html {
    /// The type of a Node in the parsed HTML tree.
    enum class NodeType {
        /**
         * A text node.
         * @see TextNode
         */
        Text,
        /**
         * An element node.
         * @see ElementNode
         */
        Element,
    };
}

#endif
