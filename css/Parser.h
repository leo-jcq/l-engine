#ifndef L_ENGINE_PARSER_H
#define L_ENGINE_PARSER_H

#include "Stylesheet.h"
#include "../BaseParser.h"

namespace css {
    /// A class for parsing CSS input strings into a Stylesheet.
    class Parser : public BaseParser {
    public:
        /**
         * Construct a new Parser object with the given input string.
         * @param input The input string to be parsed.
         */
        explicit Parser(std::string input);

        /**
         * Parse the input string.
         * @return The parsed Stylesheet.
         */
        Stylesheet parse();

    private:
        /**
         * Parse all rules from the input until the end of the stylesheet is reached.
         * @return The parsed rules.
         */
        std::vector<Rule> parseRules();

        /**
         * Parse a single rule from the input, consisting of a selector list and a declaration block.
         * @return The parsed Rule.
         */
        Rule parseRule();

        /**
         * Parse a comma-separated list of selectors from the input, sorted by ascending specificity.
         * @return The parsed selectors.
         * @throws runtime_error If an unexpected character is encountered in the selector list.
         */
        std::vector<Selector> parseSelectors();

        /**
         * Parse a single selector from the input (e.g. "div.foo#bar").
         * @return The parsed Selector.
         */
        Selector parseSelector();

        /**
         * Parse the declarations of a rule from the input, enclosed in "{" and "}".
         * @return The parsed declarations.
         */
        std::vector<Declaration> parseDeclarations();

        /**
         * Parse a single declaration from the input, e.g. "color: red;".
         * @return The parsed Declaration.
         */
        Declaration parseDeclaration();

        /**
         * Parse a color value from the input, in the form "rgb(r, g, b)" or "rgba(r, g, b, a)".
         * @return The parsed Color.
         */
        Color parseColor();

        /**
         * Parse a dimension value from the input, consisting of a number followed by an optional unit (e.g. "10px").
         * @return The parsed Dimension.
         */
        Dimension parseDimension();

        /**
         * Check if the given character is valid inside a CSS identifier (tag name, class, or id).
         * @param c The character to check.
         * @return @code true@endcode if the character is a letter, '-' or '_', @code false@endcode otherwise.
         */
        static bool isValidIdentifierChar(const char c) {
            return static_cast<bool>(std::isalpha(static_cast<unsigned char>(c))) || c == '-' || c == '_';
        }

        /**
         * Parse a name from the input, consisting of alphanumeric characters.
         * @return A string containing the parsed name.
         */
        std::string parseIdentifier() {
            return consumeWhile(isValidIdentifierChar);
        }

        /**
         * Parse a raw number from the input, consisting of digits and '.'.
         * @return A string containing the parsed number.
         */
        std::string parseNumber() {
            return consumeWhile([](const char c) {
                return std::isdigit(c) || c == '.' || c == '-';
            });
        }

        /**
         * Consume a number from the input and parse it as an integer.
         * @return The parsed integer value.
         * @throws invalid_argument If the consumed characters do not form a valid integer.
         */
        int consumeInt() {
            return std::stoi(parseNumber());
        }

        /**
         * Consume a number from the input and parse it as a float.
         * @return The parsed float value.
         * @throws invalid_argument If the consumed characters do not form a valid float.
         */
        float consumeFloat() {
            return std::stof(parseNumber());
        }

        /**
         * Consume a single color channel value (0-255) from the input, optionally followed by a comma separator.
         * @param expectNextComma Whether a "," separator is expected after the value. Defaults to @code true@endcode.
         * @return The parsed channel value.
         */
        int consumeColorValue(const bool expectNextComma = true) {
            const int value = consumeInt();
            consumeWhiteSpace();

            if (expectNextComma) {
                expect(",");
                consumeWhiteSpace();
            }

            return value;
        }
    };
}

#endif
