#pragma once

#include <string>
#include <vector>

#include "sa2026/core/IAction.h"
#include "sa2026/core/State.h"
#include "sa2026/problems/incomplete_code/wordladder/WordDictionary.h"

namespace sa2026::problems::incomplete_code::wordladder {

/*
 * STUDENT TASK: finish this class (here and in ChangeLetterAction.cpp).
 *
 * The only action of the problem: change ONE letter of the word.
 * The new word must be in the dictionary.
 */
class ChangeLetterAction : public core::IAction {
public:
    explicit ChangeLetterAction(const WordDictionary& dictionary);

    // returns ALL the words we can reach by changing one letter
    std::vector<core::StatePtr> apply(const core::StatePtr& s) const override;

    std::string getName() const override;

private:
    // TODO: add the fields you need.

};

}  // namespace sa2026::problems::incomplete_code::wordladder
