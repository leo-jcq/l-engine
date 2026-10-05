# L-Engine

For english documentation, see [README.en.md](README.en.md).

## Sommaire

## Introduction

A simple web browser engine written in C++.

Moteur de navigateur web simple, développé en C++.

Pour l'instant, il ne parse que du HTML et du CSS basique, sans certaines fonctionnalités comme :

- HTML :
    - Les balises auto-fermantes (ex. `<img />`, `<br />`, etc.)
    - Les commentaires HTML (ex. `<!-- commentaire -->`)
    - La balise `<!DOCTYPE html>`
    - Les entités HTML (ex. `&nbsp;`, `&lt;`, etc.)
    - Les attributs booléens (ex. `disabled`)
- CSS :
    - Les sélecteurs imbriqués complexes avec des espaces (ex. `tag.class` est supporté mais pas `tag .class`)
    - Les pseudo-classes et pseudo-éléments (ex. `:active` ou `::before`)
    - Les commentaires (ex. `// ...` ou `/* ... */`)
    - Les valeurs décimales sans 0 au début (ex. `.5em`)
    - Les at-rules (ex. `@import` ou `@media`)

## Détails techniques

### Modèle

#### HTML

Un document HTML est représenté comme un arbre de nœuds. La classe de base [Node](./dom/Node.h) est le type de base de
tous les nœuds de l'arbre. Deux classes en héritent :

- [TextNode](./dom/TextNode.h) : un segment de texte du document ;
- [ElementNode](./dom/ElementNode.h) : un élément HTML. Il contient un nom de balise, une liste d'attributs et une liste
  de nœuds enfants.

Par exemple, ce document :

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

est représenté par l'arbre suivant :

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

Une feuille de style est représentée par la classe [StyleSheet](./css/Stylesheet.h), qui contient une liste
de [Rule](./css/Rule.h). Chaque règle a :

- un ou plusieurs [sélecteurs](./css/Selector.h) : un sélecteur a un nom de balise optionnel, un id optionnel et une
  liste de noms de classes ;
- une liste de [déclarations](./css/Declaration.h) : une déclaration est un nom (ex. `color`, `margin`) associé à une
  valeur.

La valeur d'une déclaration est soit :

- du texte ;
- une [couleur](./css/Color.h) ;
- une valeur numérique avec une [unité](./css/Unit.h), représentée par la classe [Dimension](./css/Dimension.h).

Par exemple, la règle suivante :

```css
h1#title {
    color: rgb(255, 0, 0);
    margin: 10px;
}
```

est représentée dans le modèle comme suit :

```
Rule
├── Selector: tagName = "h1", id = "title", classes = []
└── Declarations
    ├── name = "color",  value = Color(255, 0, 0)
    └── name = "margin", value = Dimension(10, px)
```
