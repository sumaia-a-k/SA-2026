#include <iostream>
#include <string>
#include <vector>

#include "sa2026/core/IAction.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/State.h"
#include "sa2026/problems/wordladder/WordDictionary.h"
#include "sa2026/problems/wordladder/WordLadderProblem.h"

// "using" lets us write State instead of sa2026::core::State (like import in Java)
using sa2026::core::ActionPtr;
using sa2026::core::Problem;
using sa2026::core::StatePtr;
using sa2026::problems::wordladder::WordDictionary;
using sa2026::problems::wordladder::WordLadderProblem;

/*
 * A small demo of the word ladder problem. There is no search algorithm yet.
 * We only check that the state, the action and the goal test work.
 *
 * How to run (inside the SA-2026/cpp folder, NOT its parent folder):
 *   .\run.bat sa2026.problems.wordladder.WordLadderDemo   (Windows)
 *   ./run.sh sa2026.problems.wordladder.WordLadderDemo    (Git Bash, macOS, Linux)
 * The script compiles the code again every time, so you always run the newest code.
 */

// applies the actions and picks the next state with this word (or nullptr)
// "static" here = this function is used only in this file (like private in Java)
static StatePtr moveTo(const Problem& problem, const StatePtr& state, const std::string& word) {
    for (const ActionPtr& action : problem.getActions()) {
        std::vector<StatePtr> nextStates = action->apply(state);
        for (const StatePtr& next : nextStates) {
            if (next->toString() == word) {
                return next;
            }
        }
    }
    return nullptr;
}

int main() {
    std::cout << std::boolalpha;  // print true/false (like Java), not 1/0

    WordLadderProblem problem("cat", "dog", WordDictionary::threeLetterWords());
    StatePtr start = problem.getInitialState();

    std::cout << "=== Initial state ===" << std::endl;
    std::cout << start << std::endl;
    std::cout << "Is it a goal? " << problem.isGoal(start) << std::endl;

    // one action, many next states
    std::cout << "\n=== Next states of the initial state ===" << std::endl;
    for (const ActionPtr& action : problem.getActions()) {
        std::cout << action->getName() << ": " << action->apply(start) << std::endl;
    }

    // walk by hand to the goal (this is not the shortest ladder; can you find a shorter one?)
    std::cout << "\n=== Walk by hand to the goal ===" << std::endl;
    std::vector<std::string> path = {"hat", "hot", "dot", "dog"};
    StatePtr current = start;
    std::cout << current;
    for (const std::string& word : path) {
        current = moveTo(problem, current, word);
        if (current == nullptr) {
            std::cout << "\nStopped: can not go to \"" << word << "\" from here." << std::endl;
            return 0;
        }
        std::cout << " -> " << current;
    }
    std::cout << "\nIs it a goal? " << problem.isGoal(current) << std::endl;
    return 0;
}
