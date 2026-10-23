#pragma once

#include <string>
#include <vector>

#include "sa2026/core/IAction.h"
#include "sa2026/core/State.h"
#include "sa2026/problems/wordladder/WordDictionary.h"

namespace sa2026::problems::wordladder {

/*
 * The only action of the problem: change ONE letter of the word.
 * The new word must be in the dictionary.
 *
 * Unlike the maze, this one action can give MANY next states:
 *   "cat" -> "bat", "hat", "mat", "cot", "cut", ...
 * This is why IAction::apply() returns a vector and not one State.
 *
 * The dictionary is kept here (a normal field, not static), because only the action needs it.
 * This is the "other option" we talked about in MazeState.
 */
class ChangeLetterAction : public core::IAction {
public:
    explicit ChangeLetterAction(const WordDictionary& dictionary);

    std::vector<core::StatePtr> apply(const core::StatePtr& s) const override;
    std::string getName() const override;

private:
    // Our own copy of the dictionary. Java keeps a reference; a copy is simpler in C++
    // (we do not have to think about who deletes it), and the dictionary is small.
    const WordDictionary dictionary;
};

}  // namespace sa2026::problems::wordladder
