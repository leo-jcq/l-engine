#ifndef L_ENGINE_DECLARATION_H
#define L_ENGINE_DECLARATION_H

#include <string>
#include <variant>

#include "Color.h"
#include "Dimension.h"

namespace css {
    /// The value of a CSS declaration: a raw string (e.g. a keyword like "bold"), an RGBA color, or a number with a unit.
    using Value = std::variant<std::string, Color, Dimension>;

    /// A single CSS declaration, e.g. "color: red;" or "margin: 10px;".
    class Declaration {
    public:
        /**
         * Construct a new Declaration object.
         * @param name The name of the CSS declaration (e.g. "color", "margin").
         * @param value The value of the declaration.
         */
        Declaration(std::string name, Value value);

        /**
         * Get the name of the CSS declaration (e.g. "color", "margin").
         * @return The name of the CSS declaration (e.g. "color", "margin").
         */
        [[nodiscard]] const std::string &getName() const {
            return name;
        }

        /**
         * Get the value of the property.
         * @return The value of the property.
         */
        [[nodiscard]] const Value &getValue() const {
            return value;
        }

        /**
         * Check if the value is a raw string (e.g. a keyword like "bold").
         * @return @code true@endcode if the value is a raw string, @code false@endcode otherwise.
         */
        [[nodiscard]] bool isString() const {
            return std::holds_alternative<std::string>(value);
        }

        /**
         * Check if the value is an RGBA color.
         * @return @code true@endcode if the value is an RGBA color, @code false@endcode otherwise.
         */
        [[nodiscard]] bool isColor() const {
            return std::holds_alternative<Color>(value);
        }

        /**
         * Check if the value is a number with a unit (e.g. "10px", "2em").
         * @return @code true@endcode if the value is a number with a unit, @code false@endcode otherwise.
         */
        [[nodiscard]] bool isDimension() const {
            return std::holds_alternative<Dimension>(value);
        }

    private:
        /// The name of the CSS declaration (e.g. "color", "margin").
        std::string name;
        /// The value of the declaration.
        Value value;
    };
}

#endif
