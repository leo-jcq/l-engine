#include "StyleTree.h"

#include <algorithm>

#include "../css/Stylesheet.h"

namespace style {
    StyledNode StyleTree::applyStyle(const std::unique_ptr<dom::Node>& root, const css::Stylesheet& stylesheet) {
        std::vector<StyledNode> children;
        PropertyMap specifiedValues;

        if (root->getType() == dom::NodeType::Element) {
            // Convert to ElementNode
            const auto& node = dynamic_cast<const dom::ElementNode&>(*root);

            for (const std::unique_ptr<dom::Node>& a : node.getChildren()) {
                children.push_back(applyStyle(a, stylesheet));
            }

            specifiedValues = getSpecifiedValues(node, stylesheet);
        }

        return {root, specifiedValues, children};
    }

    PropertyMap StyleTree::getSpecifiedValues(const dom::ElementNode& node, const css::Stylesheet& stylesheet) {
        std::vector<MatchedRule> rules = getMatchingRules(node, stylesheet);
        std::ranges::stable_sort(rules, [](const auto& a, const auto& b) {
            return std::get<0>(a) < std::get<0>(b);
        });

        std::unordered_map<std::string, css::Value> values;


        for (const MatchedRule& rule : rules) {
            for (const css::Declaration& declaration : std::get<1>(rule).getDeclarations()) {
                values[declaration.getName()] = declaration.getValue();
            }
        }

        return values;
    }

    std::vector<MatchedRule> StyleTree::getMatchingRules(const dom::ElementNode& node,
                                                         const css::Stylesheet& stylesheet) {
        std::vector<MatchedRule> rules;

        for (const css::Rule& rule : stylesheet.getRules()) {
            if (std::optional<MatchedRule> matchedRule = getMatchedRule(node, rule); matchedRule.has_value()) {
                rules.emplace_back(matchedRule.value());
            }
        }

        return rules;
    }

    std::optional<MatchedRule> StyleTree::getMatchedRule(const dom::ElementNode& node, const css::Rule& rule) {
        for (const css::Selector& selector : rule.getSelectors()) {
            if (matches(node, selector)) {
                return std::make_optional<MatchedRule>({selector.getSpecificity(), rule});
            }
        }

        return std::nullopt;
    }

    bool StyleTree::matches(const dom::ElementNode& node, const css::Selector& selector) {
        // Check tag selector
        if (selector.getTagName().has_value() && selector.getTagName().value() != node.getTagName()) {
            return false;
        }

        // Check id selector
        if (const std::optional<std::string>& nodeId = node.getId();
            selector.getId().has_value() && (!nodeId.has_value() || selector.getId().value() != nodeId.value())) {
            return false;
        }

        // Check class selector
        const std::unordered_set<std::string>& nodeClasses = node.getClasses();

        return std::ranges::all_of(selector.getClassName(), [nodeClasses](const std::string& className) {
            return nodeClasses.contains(className);
        });
    }
}
