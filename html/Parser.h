#ifndef L_ENGINE_PARSER_H
#define L_ENGINE_PARSER_H

#include "ElementNode.h"
#include "Node.h"
#include "TextNode.h"
#include "../BaseParser.h"

namespace html {
    /// A class for parsing HTML input strings into a tree of Node objects.
    class Parser : public BaseParser {
    public:
        /**
         * Construct a new Parser object with the given input string.
         * @param input The input string to be parsed.
         */
        explicit Parser(std::string input);

        /**
         * Parse the input string.
         * @return A unique pointer to the root node of the parsed tree.
         */
        std::unique_ptr<Node> parse();

    private:
        /**
         * Parse child nodes from the input until a closing tag is encountered.
         * @return A vector of unique pointers to Node objects representing the parsed child nodes.
         */
        std::vector<std::unique_ptr<Node> > parseNodes();

        /**
         * Parse a single node from the input, which can be either an element or a text node.
         * @return A unique pointer to a Node object representing the parsed node.
         */
        std::unique_ptr<Node> parseNode() {
            if (startsWith("<"))
                return parseElement();

            return parseText();
        }

        /**
         * Parse an element node from the input, consisting of a tag name, attributes, and child nodes.
         * @return A unique pointer to an ElementNode containing the parsed element.
         */
        std::unique_ptr<ElementNode> parseElement();

        /**
         * Parse attributes from the input, consisting of name-value pairs.
         * @return An unordered map containing the parsed attributes, where the keys are attribute names and the values are attribute values.
         */
        AttrMap parseAttributes();

        /**
         * Parse a single attribute from the input, consisting of a name and a value.
         * @return A tuple containing the parsed attribute name and value.
         */
        std::tuple<std::string, std::string> parseAttr();

        /**
         * Parse an attribute value from the input, which is enclosed in either single or double quotes.
         * @return A string containing the parsed attribute value.
         * @throw runtime_error If the attribute value is not properly enclosed in quotes.
         */
        std::string parseAttrValue();

        /**
         * Parse a text node from the input, consisting of characters until a '<' is encountered.
         * @return A unique pointer to a TextNode containing the parsed text.
         */
        std::unique_ptr<TextNode> parseText();
    };
}

#endif
