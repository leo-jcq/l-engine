#include "Parser.h"

#include <algorithm>
#include <stdexcept>
#include <utility>

#include "../utils.h"

namespace css {
    Parser::Parser(std::string input) : BaseParser(std::move(input)) {
    }

    Stylesheet Parser::parse() {
        return Stylesheet(parseRules());
    }

    std::vector<Rule> Parser::parseRules() {
        std::vector<Rule> rules;

        consumeWhiteSpace();

        while (!eof()) {
            rules.push_back(parseRule());
            consumeWhiteSpace();
        }

        return rules;
    }

    Rule Parser::parseRule() {
        return {parseSelectors(), parseDeclarations()};
    }

    std::vector<Selector> Parser::parseSelectors() {
        std::vector<Selector> selectors;

        consumeWhiteSpace();

        while (!eof()) {
            selectors.push_back(parseSelector());
            consumeWhiteSpace();

            if (const char c = nextChar(); c == ',') {
                consumeChar();
                consumeWhiteSpace();
            } else if (c == '{') {
                break;
            } else {
                throw std::runtime_error("Unexpected character " + std::string(1, c) + " in selector list");
            }
        }

        // Sort by specificity
        std::ranges::sort(selectors, [](const Selector &a, const Selector &b) {
            return a.getSpecificity() < b.getSpecificity();
        });

        return selectors;
    }

    Selector Parser::parseSelector() {
        Selector selector;

        consumeWhiteSpace();

        while (!eof()) {
            if (const char c = nextChar(); c == '#') {
                consumeChar();
                selector.setId(parseIdentifier());
            } else if (c == '.') {
                consumeChar();
                selector.addClass(parseIdentifier());
            } else if (c == '*') {
                // TODO: universal selector
                consumeChar();
            } else if (isValidIdentifierChar(c)) {
                selector.setTagName(parseIdentifier());
            } else {
                break;
            }
        }

        return selector;
    }

    std::vector<Declaration> Parser::parseDeclarations() {
        expect("{");

        std::vector<Declaration> declarations;

        consumeWhiteSpace();

        while (nextChar() != '}' && !eof()) {
            declarations.push_back(parseDeclaration());
            consumeWhiteSpace();
        }

        expect("}");

        return declarations;
    }

    Declaration Parser::parseDeclaration() {
        // Declaration name
        std::string name = parseIdentifier();
        consumeWhiteSpace();
        expect(":");
        consumeWhiteSpace();

        // Value
        Value value;

        if (startsWith("rgb")) {
            // Color value
            value = parseColor();
        } else if (const char nc = nextChar(); std::isdigit(nc) || nc == '-') {
            // Dimension (numeric) value
            value = parseDimension();
        } else {
            // String value
            value = rtrim(consumeWhile([](const char c) {
                return c != ';';
            }));
        }

        // End of declaration
        consumeWhiteSpace();
        expect(";");

        return {name, value};
    }

    Color Parser::parseColor() {
        // Consume "rgb" prefix
        consumeChar(3);

        // Check if color has alpha
        bool hasAlpha;

        if ((hasAlpha = nextChar() == 'a')) {
            // Consume it to skip it
            consumeChar();
        }

        // Color must start with "("
        expect("(");
        consumeWhiteSpace();

        // Red
        const int r = consumeColorValue();
        const int g = consumeColorValue();
        const int b = consumeColorValue(hasAlpha);

        // Alpha (default = 1)
        float a = 1;

        if (hasAlpha) {
            a = consumeFloat();
            consumeWhiteSpace();
        }

        // Check if the trailing ")" is present
        expect(")");

        return {r, g, b, a};
    }

    Dimension Parser::parseDimension() {
        // Value
        float value = consumeFloat();

        // Unit
        const std::string strUnit = consumeWhile([](const char c) {
            return std::isalnum(c) || c == '%';
        });
        expect(";");

        // Search in the units table
        const auto iterator = UnitsTable.find(strUnit);
        // If not found, then no unit
        Unit unit = iterator != UnitsTable.end() ? iterator->second : Unit::None;

        return {value, unit};
    }
}
