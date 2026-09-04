#include "Color.h"

namespace css {
    Color::Color(const int r,
                 const int g,
                 const int b,
                 const float a) : r(r > 255 ? 255 : r < 0 ? 0 : r),
                                  g(g > 255 ? 255 : g < 0 ? 0 : g),
                                  b(b > 255 ? 255 : b < 0 ? 0 : b),
                                  a(a > 1 ? 1 : a < 0 ? 0 : a) {
    }
}
