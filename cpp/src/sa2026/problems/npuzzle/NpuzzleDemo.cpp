#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "sa2026/algorithms/BFS.h"
#include "sa2026/core/IAction.h"
#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/State.h"
#include "sa2026/problems/npuzzle/NpuzzleProblem.h"

// "using" lets us write State instead of sa2026::core::State (like import in Java)
using sa2026::algorithms::BFS;
using sa2026::core::ActionPtr;
using sa2026::core::Node;
using sa2026::core::NodePtr;
using sa2026::core::Problem;
using sa2026::core::StatePtr;
using sa2026::problems::npuzzle::NpuzzleProblem;

/*
 * A small demo of the N-puzzle problem.
 * We check that the state, the actions and the goal test work,
 * and at the end we let BFS solve one board.
 *
 * How to run (inside the SA-2026/cpp folder, NOT its parent folder):
 *   .\run.bat sa2026.problems.npuzzle.NpuzzleDemo   (Windows)
 *   ./run.sh sa2026.problems.npuzzle.NpuzzleDemo    (Git Bash, macOS, Linux)
 * The script compiles the code again every time, so you always run the newest code.
 */

// finds the action with this name and applies it on the state
// "static" here = this function is used only in this file (like private in Java)
static StatePtr applyByName(const Problem& problem, const StatePtr& state, const std::string& name) {
    for (const ActionPtr& action : problem.getActions()) {
        if (action->getName() == name) {
            std::vector<StatePtr> result = action->apply(state);
            return result.empty() ? nullptr : result[0];
        }
    }
    return nullptr;
}

// writes a vector like Java's Arrays.toString(): [1, 2, 3]
static std::string listText(const std::vector<int>& numbers) {
    std::string text = "[";
    for (std::size_t i = 0; i < numbers.size(); i++) {
        text += (i == 0 ? "" : ", ") + std::to_string(numbers[i]);
    }
    return text + "]";
}

int main() {
    // std::boolalpha = print true / false (and not 1 / 0), like Java
    std::cout << std::boolalpha;

    NpuzzleProblem problem = NpuzzleProblem::medium();
    StatePtr start = problem.getInitialState();

    std::cout << "=== Initial state (the medium test) ===" << std::endl;
    std::cout << start << std::endl;
    std::cout << "Is it a goal? " << problem.isGoal(start) << std::endl;

    // try every action on the initial state (the empty cell is in a corner)
    std::cout << "\n=== Try each action on the initial state ===" << std::endl;
    for (const ActionPtr& action : problem.getActions()) {
        std::vector<StatePtr> result = action->apply(start);
        if (result.empty()) {
            std::cout << action->getName() << ": not allowed\n" << std::endl;
        } else {
            std::cout << action->getName() << ": allowed" << std::endl;
            std::cout << result[0] << std::endl;
        }
    }

    // walk by hand: the easy test needs 2 moves
    std::cout << "=== Walk by hand: the easy test ===" << std::endl;
    NpuzzleProblem easy = NpuzzleProblem::easy();
    StatePtr current = easy.getInitialState();
    std::cout << current << std::endl;
    std::vector<std::string> steps = {"Move empty right", "Move empty down"};
    for (const std::string& step : steps) {
        current = applyByName(easy, current, step);
        if (current == nullptr) {
            std::cout << "Stopped: \"" << step << "\" is not allowed here." << std::endl;
            return 0;
        }
        std::cout << step << ":" << std::endl;
        std::cout << current << std::endl;
    }
    std::cout << "Is it a goal? " << easy.isGoal(current) << std::endl;

    // only half of all boards can be solved
    std::cout << "\n=== Can these boards be solved? ===" << std::endl;
    std::vector<std::vector<int>> boards = {{1, 2, 3, 4, 5, 6, 7, 0, 8}, {1, 2, 3, 4, 5, 6, 8, 7, 0}};
    for (const std::vector<int>& board : boards) {
        std::cout << listText(board) << ": " << NpuzzleProblem::isSolvable(board) << std::endl;
    }
    try {
        NpuzzleProblem wrong({1, 2, 3, 4, 5, 6, 8, 7, 0});
    } catch (const std::invalid_argument& e) {
        std::cout << "NpuzzleProblem(...) says: " << e.what() << std::endl;
    }

    // now a search algorithm can solve it
    std::cout << "\n=== BFS (graph search) solves the medium test ===" << std::endl;
    BFS bfs(true);
    NodePtr goal = problem.solve(bfs);
    std::string moves;
    for (const Node* node : goal->getPathFromRoot()) {
        if (node->getAction() != nullptr) {
            moves += (moves.empty() ? "" : ", ") + node->getAction()->getName();
        }
    }
    std::cout << "Moves: " << moves << std::endl;
    std::cout << "Steps: " << goal->getDepth() << ", expanded: " << bfs.getNodesActuallyExpanded()
              << ", generated: " << bfs.getGeneratedNodes() << std::endl;
    return 0;
}
