# L-Engine

A simple web browser engine written in C++.

For now, it only parses basic HTML without certain features like :

- Self-closing tags (e.g. `<img />`, `<br />`, etc.)
- HTML comments (e.g. `<!-- comment -->`)
- The `<!DOCTYPE html>` tag
- HTML entities (e.g. `&nbsp;`, `&lt;`, etc.)
- Boolean attributes (e.g. `disabled`)
