#include "Declaration.h"

namespace css {
    Declaration::Declaration(std::string name, Value value) : name(std::move(name)), value(std::move(value)) {
    }
}
