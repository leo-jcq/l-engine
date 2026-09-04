#ifndef L_ENGINE_STYLESHEET_H
#define L_ENGINE_STYLESHEET_H

#include <vector>

#include "Rule.h"

namespace css {
    /// A parsed CSS stylesheet, i.e. an ordered collection of rules.
    class Stylesheet {
    public:
        /**
         * Construct a new Stylesheet object.
         * @param rules The rules making up this stylesheet.
         */
        explicit Stylesheet(std::vector<Rule> rules);

    private:
        /// The rules making up this stylesheet.
        std::vector<Rule> rules;
    };
}

#endif
