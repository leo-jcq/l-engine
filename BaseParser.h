#ifndef L_ENGINE_BASEPARSER_H
#define L_ENGINE_BASEPARSER_H

#include <functional>
#include <string>
#include <cctype>

class BaseParser {
public:
    /**
     * Construct a new Parser object with the given input string.
     * @param input The input string to be parsed.
     */
    explicit BaseParser(std::string input);

    /// Destroy the Parser object.
    virtual ~BaseParser() = default;

protected:
    /// The current position in the input string.
    size_t pos;

    /**
     * Read the current character without consuming it.
     * @return The current character.
     */
    [[nodiscard]] char nextChar() const {
        return input[pos];
    }

    /**
     * Check if the input starts with the given string.
     * @param s The string to check for.
     * @return @code true@endcode if the input starts with the given string, @code false@endcode otherwise.
     */
    [[nodiscard]] bool startsWith(const std::string &s) const;

    /**
     * Consume the given string from the input.
     * If the input does not start with the given string, an exception is thrown.
     * @param s The string to consume.
     * @throws runtime_error The input does not start with the given string.
     */
    void expect(const std::string &s);

    /**
     * Check if the end of the input has been reached.
     * @return @code true@endcode if the end of the input has been reached, @code false@endcode otherwise.
     */
    [[nodiscard]] bool eof() const {
        return pos >= input.size();
    }

    /**
     * Consume the current character and return it.
     * @return The current character.
     */
    char consumeChar() {
        const char c = nextChar();
        pos++;
        return c;
    }

    /**
     * Consume the given number of characters from the input and return them as a string.
     * @param count The number of characters to consume.
     * @return A string containing the consumed characters.
     */
    std::string consumeChar(const int count) {
        // Get chars
        std::string chars = input.substr(pos, count);

        pos += count;

        return chars;
    }

    /**
     * Consume characters from the input while the given test function returns true.
     * @param test A function that takes a character and returns true if it should be consumed, false otherwise.
     * @return A string containing the consumed characters.
     */
    std::string consumeWhile(const std::function<bool (char)> &test);

    /// Consume whitespace characters from the input
    void consumeWhiteSpace() {
        consumeWhile([](const char c) { return static_cast<bool>(std::isspace(static_cast<unsigned char>(c))); });
    }

    /**
     * Parse a name from the input, consisting of alphanumeric characters.
     * @return A string containing the parsed name.
     */
    std::string parseName() {
        return consumeWhile([](const char c) {
            return static_cast<bool>(std::isalnum(static_cast<unsigned char>(c)));
        });
    }

private:
    /// The input string to be parsed.
    std::string input;
};

#endif
