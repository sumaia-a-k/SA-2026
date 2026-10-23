#pragma once

#include <string>
#include <vector>

#include "sa2026/core/IAction.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/State.h"
#include "sa2026/problems/wordladder/WordDictionary.h"

namespace sa2026::problems::wordladder {

/*
 * The word ladder problem: change the start word into the goal word,
 * one letter at a time. Every word on the way must be in the dictionary.
 *
 * Example: cat -> hat -> hot -> dot -> dog
 *
 * Initial state: the start word.
 * Goal:          the goal word.
 * Actions:       change one letter (only one action, but it gives many states).
 * Cost:          every change costs 1.
 */
class WordLadderProblem : public core::Problem {
public:
    WordLadderProblem(const std::string& startWord, const std::string& goalWord,
                      const WordDictionary& dictionary);

    core::StatePtr getInitialState() const override;
    bool isGoal(const core::StatePtr& state) const override;
    std::vector<core::ActionPtr> getActions() const override;
    double getActionCost(const core::StatePtr& s, const core::ActionPtr& a,
                         const core::StatePtr& next) const override;

private:
    core::StatePtr initialState;
    std::vector<core::ActionPtr> actions;
};

}  // namespace sa2026::problems::wordladder
