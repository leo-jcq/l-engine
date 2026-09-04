cmake_minimum_required(VERSION 4.2)
project(l-engine)

set(CMAKE_CXX_STANDARD 20)

add_executable(l-engine main.cpp
        BaseParser.cpp
        BaseParser.h
        html/Node.h
        html/Node.cpp
        html/NodeType.h
        html/TextNode.h
        html/TextNode.cpp
        html/ElementNode.h
        html/ElementNode.cpp
        html/Parser.h
        html/Parser.cpp
        css/Selector.cpp
        css/Selector.h
        css/Rule.cpp
        css/Rule.h
        css/Declaration.cpp
        css/Declaration.h
        css/Color.h
        css/Color.cpp
        css/Unit.h
        css/Dimension.cpp
        css/Dimension.h
        css/Parser.cpp
        css/Parser.h
        css/Stylesheet.cpp
        css/Stylesheet.h
        utils.h
        utils.h)
