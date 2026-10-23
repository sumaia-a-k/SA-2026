#pragma once

#include <cstddef>
#include <string>

#include "sa2026/core/State.h"

namespace sa2026::problems::wordladder {

/*
 * A state of the word ladder problem = the current word, for example "cat".
 */
class WordLadderState : public core::State {
public:
    explicit WordLadderState(const std::string& word);

    static void setGoalWord(const std::string& newGoalWord);

    std::string getWord() const;

    bool isGoal() const override;
    std::string toString() const override;
    bool equals(const core::State& other) const override;
    std::size_t hashCode() const override;

private:
    /*
     * The goal word is NOT part of the state. It is the same for all states.
     * Like the maze in MazeState, it is static: one copy for all states.
     * WordLadderProblem sets it once, before the search starts.
     */
    inline static std::string goalWord;

    const std::string word;
};

}  // namespace sa2026::problems::wordladder
