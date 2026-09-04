#include "BaseParser.h"

#include <stdexcept>
#include <utility>

BaseParser::BaseParser(std::string input) : pos(0), input(std::move(input)) {
}

bool BaseParser::startsWith(const std::string &s) const {
    return input.compare(pos, s.size(), s) == 0;
}

void BaseParser::expect(const std::string &s) {
    if (startsWith(s)) {
        pos += s.size();
    } else {
        throw std::runtime_error("Expected " + s + " at byte " + std::to_string(pos) + " but it was not found");
    }
}

std::string BaseParser::consumeWhile(const std::function<bool (char)> &test) {
    std::string result;

    while (!eof() && test(nextChar())) {
        result += consumeChar();
    }

    return result;
}
