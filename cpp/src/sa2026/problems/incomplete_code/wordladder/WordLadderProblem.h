#pragma once

#include <string>
#include <vector>

#include "sa2026/core/IAction.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/State.h"
#include "sa2026/problems/incomplete_code/wordladder/WordDictionary.h"

namespace sa2026::problems::incomplete_code::wordladder {

/*
 * STUDENT TASK: finish this class (here and in WordLadderProblem.cpp).
 *
 * The word ladder problem: change the start word into the goal word,
 * one letter at a time. Every word on the way must be in the dictionary.
 *
 * Example: cat -> hat -> hot -> dot -> dog
 *
 * Every change costs 1.
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
    // TODO: add the fields you need.

};

}  // namespace sa2026::problems::incomplete_code::wordladder
