#include <string>
#include <fstream>

#include "files.h"

std::string openAndRead(const char *path) {
    std::ifstream in(path);
    return {(std::istreambuf_iterator(in)), std::istreambuf_iterator<char>()};
}
