#include "sa2026/problems/wordladder/WordLadderState.h"

#include <functional>

namespace sa2026::problems::wordladder {

WordLadderState::WordLadderState(const std::string& word) : word(word) {}

void WordLadderState::setGoalWord(const std::string& newGoalWord) {
    goalWord = newGoalWord;
}

std::string WordLadderState::getWord() const {
    return word;
}

bool WordLadderState::isGoal() const {
    return word == goalWord;  // in C++, == compares the letters of two strings
}

std::string WordLadderState::toString() const {
    return word;
}

// two states are equal when they have the same word
bool WordLadderState::equals(const core::State& other) const {
    if (this == &other) return true;
    const WordLadderState* o = dynamic_cast<const WordLadderState*>(&other);
    if (o == nullptr) return false;
    return word == o->word;
}

/*
 * We use the hash of the string itself.
 * std::hash<std::string> is the C++ hash for strings (like String.hashCode() in Java).
 * Here we do NOT know all the possible values (any word can come),
 * so we let the library make a good hash for us.
 * Compare with MazeState, where we know the ranges and can have no conflicts at all.
 */
std::size_t WordLadderState::hashCode() const {
    return std::hash<std::string>{}(word);
}

}  // namespace sa2026::problems::wordladder
