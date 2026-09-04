#include "Selector.h"

namespace css {
    Specificity Selector::getSpecificity() const {
        int a = id.has_value() ? 1 : 0;
        int b = static_cast<int>(className.size());
        int c = tagName.has_value() ? 1 : 0;

        return {a, b, c};
    }
}
