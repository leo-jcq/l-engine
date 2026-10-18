#include "utils.h"

namespace css {
    float valueToPx(const Value& value) {
        if (std::holds_alternative<Dimension>(value)) {
            if (const auto& dimensionValue = std::get<Dimension>(value); dimensionValue.unit == Unit::Px) {
                return dimensionValue.value;
            }
        }

        return 0;
    }
}
