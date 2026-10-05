#include "EdgeSizes.h"

namespace layout {
    EdgeSizes::EdgeSizes() : top(0), right(0), bottom(0), left(0) {
    }

    EdgeSizes::EdgeSizes(const float top, const float right, const float bottom, const float left) :
        top(top), right(right), bottom(bottom), left(left) {
    }
}
