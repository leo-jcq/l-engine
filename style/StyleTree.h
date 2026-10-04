#ifndef L_ENGINE_STYLETREE_H
#define L_ENGINE_STYLETREE_H

#include "StyledNode.h"
#include "../css/Rule.h"
#include "../css/Selector.h"
#include "../css/Stylesheet.h"
#include "../dom/ElementNode.h"

namespace style {
    /// A CSS rule that has been matched to a DOM element, along with its specificity.
    using MatchedRule = std::tuple<css::Specificity, css::Rule>;

    /// A tree of styled nodes, i.e. a DOM tree with associated CSS styles.
    class StyleTree {
    public:
        /**
         * Apply the given stylesheet to the given DOM tree, producing a tree of styled nodes.
         * @param root The root of the DOM tree to style.
         * @param stylesheet The stylesheet to apply to the DOM tree.
         * @return The root of the resulting tree of styled nodes.
         */
        static StyledNode applyStyle(const std::unique_ptr<dom::Node>& root, const css::Stylesheet& stylesheet);

    private:
        /**
         * Apply style to a single element.
         * @param node The DOM element to style.
         * @param stylesheet The stylesheet to apply to the element.
         * @return A map of CSS property names to their computed values for the element.
         */
        static PropertyMap getSpecifiedValues(const dom::ElementNode& node, const css::Stylesheet& stylesheet);


        /**
         * Find all the CSS rules that match the given DOM element, along with their specificity.
         * @param node The DOM element to match against the stylesheet.
         * @param stylesheet The stylesheet to match against the DOM element.
         * @return A vector of matched rules, each consisting of a specificity and a rule.
         */
        static std::vector<MatchedRule> getMatchingRules(const dom::ElementNode& node, const css::Stylesheet& stylesheet);

        /**
         * Check if a given CSS rule matches a given DOM element, and if so, return the matched rule along with its specificity.
         * @param node The DOM element to check against the rule.
         * @param rule The CSS rule to check against the DOM element.
         * @return An optional matched rule, which is present if the rule matches the element, and absent otherwise.
         */
        static std::optional<MatchedRule> getMatchedRule(const dom::ElementNode& node, const css::Rule& rule);

        /**
         * Check if a given CSS selector matches a given DOM element.
         * @param node The DOM element to check against the selector.
         * @param selector The CSS selector to check against the DOM element.
         * @return True if the selector matches the element, false otherwise.
         */
        static bool matches(const dom::ElementNode& node, const css::Selector& selector);
    };
}


#endif
