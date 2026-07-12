cmake_minimum_required(VERSION 4.2)
project(l-engine)

set(CMAKE_CXX_STANDARD 20)

add_executable(l-engine main.cpp
        html/Node.h
        html/Node.cpp
        html/NodeType.h
        html/TextNode.h
        html/TextNode.cpp
        html/ElementNode.h
        html/ElementNode.cpp
        html/Parser.h
        html/Parser.cpp)
