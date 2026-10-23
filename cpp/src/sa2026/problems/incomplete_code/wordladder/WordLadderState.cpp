#include "sa2026/problems/incomplete_code/wordladder/WordLadderState.h"

namespace sa2026::problems::incomplete_code::wordladder {

WordLadderState::WordLadderState(const std::string& word) {
    // TODO
}

bool WordLadderState::isGoal() const {
    // TODO
    return false;
}

std::string WordLadderState::toString() const {
    // TODO: return the word
    return "";
}

bool WordLadderState::equals(const core::State& other) const {
    // TODO
    return false;
}

std::size_t WordLadderState::hashCode() const {
    // TODO
    //   Question: can we make a hash with no conflicts here, like in MazeState? Why?
    return 0;
}

}  // namespace sa2026::problems::incomplete_code::wordladder
