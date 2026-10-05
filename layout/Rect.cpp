#include "Rect.h"

namespace layout {
    Rect::Rect() : x(0), y(0), width(0), height(0) {
    }

    Rect::Rect(const float x, const float y, const float width, const float height) : x(x), y(y), width(width),
        height(height) {
    }
}
