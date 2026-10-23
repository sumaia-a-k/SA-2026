#include "sa2026/problems/incomplete_code/wordladder/ChangeLetterAction.h"

#include <memory>

#include "sa2026/problems/incomplete_code/wordladder/WordLadderState.h"  // you will need it

namespace sa2026::problems::incomplete_code::wordladder {

ChangeLetterAction::ChangeLetterAction(const WordDictionary& dictionary) {
    // TODO
}

// returns ALL the words we can reach by changing one letter
std::vector<core::StatePtr> ChangeLetterAction::apply(const core::StatePtr& s) const {
    // TODO
    //   Question: in the maze, apply() gives 0 or 1 state. How many can it give here?
    return {};
}

std::string ChangeLetterAction::getName() const {
    return "Change one letter";
}

}  // namespace sa2026::problems::incomplete_code::wordladder
