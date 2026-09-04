#include "Stylesheet.h"

#include <utility>

namespace css {
    Stylesheet::Stylesheet(std::vector<Rule> rules) : rules(std::move(rules)) {
    }
}
