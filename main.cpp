#include <iostream>

#include "files.h"
#include "html/Parser.h"

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Error : no file path provided. Usage : " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    const std::string fileContent = openAndRead(argv[1]);

    html::Parser parser(fileContent);
    const std::unique_ptr<html::Node> node = parser.parse();

    std::string html;
    node->toHTML(html, 0);

    std::cout << html;

    return 0;
}
