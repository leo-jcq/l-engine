#ifndef L_ENGINE_UTILS_H
#define L_ENGINE_UTILS_H

#include <string>

inline auto ws = " \t\n\r\f\v";

/**
 * Trim whitespace from the end of a string.
 * @param s The string to trim.
 * @return The string with whitespace removed from the end.
 */
inline std::string rtrim(std::string s) {
    s.erase(s.find_last_not_of(ws) + 1);
    return s;
}

#endif
