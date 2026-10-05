# L-Engine

## Summary

- [Introduction](#introduction)
- [How it works](#how-it-works)
  - [Model](#model)
    - [HTML](#html)
    - [CSS](#css)

## Introduction

A simple web browser engine written in C++.

For now, it only parses basic HTML and CSS without certain features like :

- HTML:
    - Self-closing tags (e.g. `<img />`, `<br />`, etc.)
    - HTML comments (e.g. `<!-- comment -->`)
    - The `<!DOCTYPE html>` tag
    - HTML entities (e.g. `&nbsp;`, `&lt;`, etc.)
    - Boolean attributes (e.g. `disabled`)
- CSS:
    - Complex nested selectors with spaces (e.g. `tag.class` is supported but `tag .class` isn't)
    - Pseudo-classes and pseudo-elements (e.g. `:active` or `::before`)
    - Comments (e.g. `// ...` or `/* ... */`)
    - Decimal value without a 0 at the start (e.g. `.5em`)
    - At-rules (e.g. `@import` or `@media`)

## How it works

### Model

#### HTML

An HTML document is represented as a tree of nodes. The base class [Node](./dom/Node.h) is the common type of all
nodes in the tree. Two classes derive from it:

- [TextNode](./dom/TextNode.h): a text segment of the document.
- [ElementNode](./dom/ElementNode.h): an HTML element. It holds a tag name, a list of attributes and a list of child
  nodes.

For example, this document:

```html
<html>
    <head>
        <title>My page</title>
    </head>
    <body>
        <h1 id="title">Hello world</h1>
    </body>
</html>
```

is represented by the following tree:

```
html                      // ElementNode
├── head                  // ElementNode
│   └── title             // ElementNode
│       └── "My page"     // TextNode
└── body                  // ElementNode
    └── h1                // ElementNode (attribute: id = "title")
        └── "Hello world" // TextNode
```

#### CSS

A stylesheet is represented by the [StyleSheet](./css/Stylesheet.h) class, which contains a list of
[Rule](./css/Rule.h). Each rule has:

- one or more [selectors](./css/Selector.h): a selector has an optional tag name, an optional id and a list of class
  names;
- a list of [declarations](./css/Declaration.h): a declaration is a name (e.g. `color`, `margin`) associated with a
  value.

A declaration value is one of:

- text;
- a [color](./css/Color.h);
- a numeric value with a [unit](./css/Unit.h), represented by the [Dimension](./css/Dimension.h) class.

For example, the following rule:

```css
h1#title {
    color: rgb(255, 0, 0);
    margin: 10px;
}
```

is mapped to the model as follows:

```
Rule
├── Selector: tagName = "h1", id = "title", classes = []
└── Declarations
    ├── name = "color",  value = Color(255, 0, 0)
    └── name = "margin", value = Dimension(10, px)
```
