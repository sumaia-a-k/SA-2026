#include <iostream>
#include <string>
#include <vector>

#include "sa2026/core/IAction.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/State.h"
#include "sa2026/problems/maze/Maze.h"
#include "sa2026/problems/maze/MazeProblem.h"

// "using" lets us write State instead of sa2026::core::State (like import in Java)
using sa2026::core::ActionPtr;
using sa2026::core::Problem;
using sa2026::core::StatePtr;
using sa2026::problems::maze::Maze;
using sa2026::problems::maze::MazePtr;
using sa2026::problems::maze::MazeProblem;

/*
 * A small demo of the maze problem. There is no search algorithm yet.
 * We only check that the state, the actions and the goal test work.
 *
 * How to run (inside the SA-2026/cpp folder, NOT its parent folder):
 *   .\run.bat sa2026.problems.maze.MazeDemo   (Windows)
 *   ./run.sh sa2026.problems.maze.MazeDemo    (Git Bash, macOS, Linux)
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

int main() {
    std::cout << std::boolalpha;  // print true/false (like Java), not 1/0

    MazePtr maze = Maze::fromLines({
            "S.#....",
            ".##.##.",
            "....#..",
            ".##....",
            "...#.#G"});

    MazeProblem problem(maze);
    StatePtr start = problem.getInitialState();

    std::cout << "=== Initial state ===" << std::endl;
    std::cout << start << std::endl;
    std::cout << "Is it a goal? " << problem.isGoal(start) << std::endl;

    // try every action on the initial state
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

    // walk by hand to the goal: down 2, right 3, down 1, right 3, down 1
    std::cout << "=== Walk by hand to the goal ===" << std::endl;
    std::vector<std::string> path = {"Move down", "Move down",
                                     "Move right", "Move right", "Move right",
                                     "Move down",
                                     "Move right", "Move right", "Move right",
                                     "Move down"};
    StatePtr current = start;
    for (const std::string& step : path) {
        current = applyByName(problem, current, step);
        if (current == nullptr) {
            std::cout << "Stopped: \"" << step << "\" is not allowed here." << std::endl;
            return 0;
        }
    }
    std::cout << current << std::endl;
    std::cout << "Is it a goal? " << problem.isGoal(current) << std::endl;
    return 0;
}
