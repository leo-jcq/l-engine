#ifndef L_ENGINE_SELECTOR_H
#define L_ENGINE_SELECTOR_H

#include <optional>
#include <string>
#include <vector>

namespace css {
    /// The specificity of a selector, as a (id count, class count, tag count) tuple used to order matching rules.
    using Specificity = std::tuple<int, int, int>;

    /// A single CSS selector, e.g. "div.foo#bar".
    class Selector {
    public:
        /**
         * Set the tag name of this selector (e.g. "div").
         * @param newTagName The tag name to match.
         */
        void setTagName(std::string newTagName) {
            tagName = std::move(newTagName);
        }

        /**
         * Set the id of this selector (e.g. "bar" for "#bar").
         * @param newId The id to match.
         */
        void setId(std::string newId) {
            id = std::move(newId);
        }

        /**
         * Add a class to this selector (e.g. "foo" for ".foo").
         * @param newClass The class name to match.
         */
        void addClass(std::string newClass) {
            className.push_back(std::move(newClass));
        }

        /**
         * Compute the specificity of this selector, used to determine which rule wins when several match the same element.
         * @return The specificity of this selector, as a (id count, class count, tag count) tuple.
         */
        [[nodiscard]] Specificity getSpecificity() const;

    private:
        /// The tag name to match (e.g. "div"), if any.
        std::optional<std::string> tagName;
        /// The id to match (e.g. "bar" for "#bar"), if any.
        std::optional<std::string> id;
        /// The class names to match (e.g. "foo" for ".foo").
        std::vector<std::string> className;
    };
}

#endif
