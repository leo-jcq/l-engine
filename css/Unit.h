#ifndef L_ENGINE_UNIT_H
#define L_ENGINE_UNIT_H

#include <string>
#include <unordered_map>

namespace css {
    /// The unit of a numeric CSS value.
    enum class Unit {
        /// Value without unit (ex: line-height: 1.5)
        None,
        /// Pixels (px).
        Px,
        /// Font-relative unit, relative to the parent element's font size (em).
        Em,
        /// Font-relative unit, relative to the root element's font size (rem).
        Rem,
        /// Percentage of a reference value (%).
        Percent
    };

    /// Lookup table mapping the raw unit suffix parsed from the input (e.g. "px") to its Unit value.
    inline const std::unordered_map<std::string, Unit> UnitsTable = {
        {"px", Unit::Px},
        {"em", Unit::Em},
        {"rem", Unit::Rem},
        {"%", Unit::Percent}
    };
}

#endif
