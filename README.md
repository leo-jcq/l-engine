# L-Engine

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
