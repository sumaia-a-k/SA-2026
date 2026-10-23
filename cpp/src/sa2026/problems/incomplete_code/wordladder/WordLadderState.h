#pragma once

#include <cstddef>
#include <string>

#include "sa2026/core/State.h"

namespace sa2026::problems::incomplete_code::wordladder {

/*
 * STUDENT TASK: finish this class (here and in WordLadderState.cpp).
 *
 * A state of the word ladder problem = the current word, for example "cat".
 */
class WordLadderState : public core::State {
public:
    explicit WordLadderState(const std::string& word);

    bool isGoal() const override;
    std::string toString() const override;
    bool equals(const core::State& other) const override;
    std::size_t hashCode() const override;

private:
    // TODO: add the fields you need.
    //       Question: is the goal word part of the state? Where should it be kept?

};

}  // namespace sa2026::problems::incomplete_code::wordladder
