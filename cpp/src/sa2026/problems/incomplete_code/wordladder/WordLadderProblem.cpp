#include "sa2026/problems/incomplete_code/wordladder/WordLadderProblem.h"

#include <memory>
#include <stdexcept>

#include "sa2026/problems/incomplete_code/wordladder/ChangeLetterAction.h"  // you will need them
#include "sa2026/problems/incomplete_code/wordladder/WordLadderState.h"

namespace sa2026::problems::incomplete_code::wordladder {

WordLadderProblem::WordLadderProblem(const std::string& startWord, const std::string& goalWord,
                                     const WordDictionary& dictionary) {
    // TODO
    //   Question: what should happen if the two words have different lengths?
}

core::StatePtr WordLadderProblem::getInitialState() const {
    // TODO
    return nullptr;
}

bool WordLadderProblem::isGoal(const core::StatePtr& state) const {
    // TODO
    return false;
}

std::vector<core::ActionPtr> WordLadderProblem::getActions() const {
    // TODO
    return {};
}

double WordLadderProblem::getActionCost(const core::StatePtr& s, const core::ActionPtr& a,
                                        const core::StatePtr& next) const {
    // TODO
    return 0;
}

}  // namespace sa2026::problems::incomplete_code::wordladder
