#include "sa2026/problems/wordladder/WordLadderProblem.h"

#include <memory>
#include <stdexcept>

#include "sa2026/problems/wordladder/ChangeLetterAction.h"
#include "sa2026/problems/wordladder/WordLadderState.h"

namespace sa2026::problems::wordladder {

WordLadderProblem::WordLadderProblem(const std::string& startWord, const std::string& goalWord,
                                     const WordDictionary& dictionary) {
    if (startWord.size() != goalWord.size()) {
        throw std::invalid_argument("The start and goal words must have the same length.");
    }
    WordLadderState::setGoalWord(toLowerCase(goalWord));
    initialState = std::make_shared<WordLadderState>(toLowerCase(startWord));
    actions.push_back(std::make_shared<ChangeLetterAction>(dictionary));
}

core::StatePtr WordLadderProblem::getInitialState() const {
    return initialState;
}

bool WordLadderProblem::isGoal(const core::StatePtr& state) const {
    return state->isGoal();
}

std::vector<core::ActionPtr> WordLadderProblem::getActions() const {
    return actions;
}

double WordLadderProblem::getActionCost(const core::StatePtr& s, const core::ActionPtr& a,
                                        const core::StatePtr& next) const {
    return 1;
}

}  // namespace sa2026::problems::wordladder
