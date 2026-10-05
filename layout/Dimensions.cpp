#include "Dimensions.h"

#include <algorithm>

namespace layout {
    Dimensions::Dimensions() : content(Rect()), padding(EdgeSizes()), border(EdgeSizes()), margin(EdgeSizes()) {
    }

    Dimensions::Dimensions(Rect content, EdgeSizes padding, EdgeSizes border, EdgeSizes margin) :
        content(std::move(content)), padding(std::move(padding)), border(std::move(border)), margin(std::move(margin)) {
    }
}
