#include "sa2026/core/State.h"

namespace sa2026::core {

std::ostream& operator<<(std::ostream& out, const StatePtr& state) {
    if (state == nullptr) {
        return out << "null";
    }
    return out << state->toString();
}

std::ostream& operator<<(std::ostream& out, const std::vector<StatePtr>& states) {
    out << "[";
    for (std::size_t i = 0; i < states.size(); i++) {
        if (i > 0) {
            out << ", ";
        }
        out << states[i];
    }
    return out << "]";
}

}  // namespace sa2026::core
