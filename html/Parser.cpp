#include "Parser.h"

#include <utility>

namespace html {
    Parser::Parser(std::string input) : BaseParser(std::move(input)) {
    }

    std::unique_ptr<Node> Parser::parse() {
        std::vector<std::unique_ptr<Node> > nodes = parseNodes();

        if (!eof()) {
            throw std::runtime_error("Unexpected content at byte " + std::to_string(pos));
        }

        if (nodes.size() == 1) {
            return std::move(nodes[0]);
        }

        return std::make_unique<ElementNode>("html", AttrMap(), std::move(nodes));
    }

    std::vector<std::unique_ptr<Node> > Parser::parseNodes() {
        std::vector<std::unique_ptr<Node> > nodes;

        consumeWhiteSpace();

        while (!eof() && !startsWith("</")) {
            nodes.push_back(parseNode());
        }

        return nodes;
    }

    std::unique_ptr<ElementNode> Parser::parseElement() {
        // Opening tag
        expect("<");
        std::string tagName = parseName();
        AttrMap attrs = parseAttributes();
        expect(">");

        // Content
        std::vector<std::unique_ptr<Node> > children = parseNodes();

        // Closing tag
        expect("</");
        expect(tagName);
        expect(">");

        return std::make_unique<ElementNode>(std::move(tagName), std::move(attrs), std::move(children));
    }

    AttrMap Parser::parseAttributes() {
        AttrMap attributes;

        consumeWhiteSpace();

        while (!eof() && nextChar() != '>') {
            auto [name, value] = parseAttr();
            attributes.emplace(std::move(name), std::move(value));
            consumeWhiteSpace();
        }

        if (eof()) {
            throw std::runtime_error("Unexpected end of input while parsing attributes at byte " + std::to_string(pos));
        }

        return attributes;
    }

    std::tuple<std::string, std::string> Parser::parseAttr() {
        std::string name = parseName();
        expect("=");
        std::string value = parseAttrValue();
        return {std::move(name), std::move(value)};
    }

    std::string Parser::parseAttrValue() {
        const char openQuote = consumeChar();
        if (openQuote != '"' && openQuote != '\'') {
            throw std::runtime_error(
                "Expected \" or ' at byte " + std::to_string(pos) + " but was " + std::string(1, openQuote) + " found"
            );
        }

        std::string value = consumeWhile([openQuote](const char c) { return c != openQuote; });

        if (const char closeQuote = consumeChar(); openQuote != closeQuote) {
            throw std::runtime_error("Open and close quote are different for attribute");
        }

        return value;
    }

    std::unique_ptr<TextNode> Parser::parseText() {
        return std::make_unique<TextNode>(consumeWhile([](const char c) { return c != '<'; }));
    }
}
