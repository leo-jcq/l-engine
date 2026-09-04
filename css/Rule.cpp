#include "Rule.h"

namespace css {
    Rule::Rule(std::vector<Selector> selectors,
               std::vector<Declaration> declarations) : selectors(std::move(selectors)),
                                                        declarations(std::move(declarations)) {
    }
}
