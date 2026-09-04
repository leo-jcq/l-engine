#ifndef L_ENGINE_RULE_H
#define L_ENGINE_RULE_H

#include <vector>

#include "Declaration.h"
#include "Selector.h"

namespace css {
    /// A single CSS rule, i.e. one or more selectors sharing a block of declarations (e.g. "div, .foo { color: red; }").
    class Rule {
    public:
        /**
         * Construct a new Rule object.
         * @param selectors The selectors matching the elements this rule applies to.
         * @param declarations The declarations to apply to matching elements.
         */
        Rule(std::vector<Selector> selectors, std::vector<Declaration> declarations);

    private:
        /// The selectors matching the elements this rule applies to.
        std::vector<Selector> selectors;
        /// The declarations to apply to matching elements.
        std::vector<Declaration> declarations;
    };
}

#endif
