#ifndef L_ENGINE_FILES_H
#define L_ENGINE_FILES_H

#include <string>

/**
 * Opens a file and reads its contents into a string.
 * @param path The path to the file to be opened.
 * @return The contents of the file as a string.
 */
std::string openAndRead(const char *path);

#endif
