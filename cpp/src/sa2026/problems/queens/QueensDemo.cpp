#include <iostream>
#include <string>
#include <vector>

#include "sa2026/algorithms/HillClimbing.h"
#include "sa2026/algorithms/RandomRestart.h"
#include "sa2026/algorithms/StochasticHillClimbing.h"
#include "sa2026/core/Node.h"
#include "sa2026/problems/queens/QueensProblem.h"

using sa2026::algorithms::HillClimbing;
using sa2026::algorithms::RandomRestart;
using sa2026::algorithms::StochasticHillClimbing;
using sa2026::core::Node;
using sa2026::core::NodePtr;
using sa2026::problems::queens::QueensProblem;

/*
 * Solves 8-queens with Hill Climbing, Stochastic Hill Climbing and Random Restart.
 *
 * How to run (inside the SA-2026/cpp folder, NOT its parent folder):
 *   .\run.bat sa2026.problems.queens.QueensDemo   (Windows)
 *   ./run.sh sa2026.problems.queens.QueensDemo    (Git Bash, macOS, Linux)
 */

// the h of every board on the path, for example "9 -> 3 -> 1 -> 0"
static std::string hPath(const NodePtr& end) {
    std::string text;
    std::vector<const Node*> path = end->getPathFromRoot();
    for (std::size_t i = 0; i < path.size(); i++) {
        if (i > 0) text += " -> ";
        text += std::to_string(static_cast<int>(path[i]->getTotalCost()));
    }
    return text;
}

// runs Hill Climbing and prints the start board, what happened and the last board
static void climb(const QueensProblem& problem) {
    HillClimbing hill;
    std::cout << problem.getInitialState()->toString();
    NodePtr goal = problem.solve(hill);
    NodePtr end = (goal != nullptr) ? goal : hill.getStuckNode();
    std::cout << (goal != nullptr ? "Solved" : "Stuck") << " after " << end->getDepth()
              << " swaps, h: " << hPath(end) << std::endl;
    std::cout << end->getState()->toString() << std::endl;
}

int main() {
    // 1. Hill Climbing on the two examples of the lesson page
    std::cout << "=== Hill Climbing, Example 1 ===" << std::endl;
    climb(QueensProblem::example1());
    std::cout << "=== Hill Climbing, Example 2 ===" << std::endl;
    climb(QueensProblem::example2());

    // 2. Stochastic Hill Climbing on Example 1: other seeds, other random choices.
    //    (Steepest Hill Climbing always solves Example 1. Stochastic does not.)
    std::cout << "=== Stochastic Hill Climbing, Example 1 ===" << std::endl;
    for (unsigned int seed = 1; seed <= 5; seed++) {
        StochasticHillClimbing stochastic(seed);
        NodePtr goal = QueensProblem::example1().solve(stochastic);
        NodePtr end = (goal != nullptr) ? goal : stochastic.getStuckNode();
        std::cout << "seed " << seed << ": " << (goal != nullptr ? "solved" : "stuck")
                  << ", h: " << hPath(end) << std::endl;
    }

    // 3. Random restart: new random boards until one climb solves it.
    //    It does not use the start board of the problem: every climb starts from a random board.
    std::cout << "\n=== Random restart (seed 10, at most 100 climbs) ===" << std::endl;
    RandomRestart restart(100, 10);
    NodePtr goal = QueensProblem::example1().solve(restart);
    if (goal == nullptr) {
        std::cout << "No goal after " << restart.getClimbs() << " climbs." << std::endl;
    } else {
        std::cout << "Solved on climb " << restart.getClimbs()
                  << " (generated " << restart.getGeneratedNodes()
                  << ", expanded " << restart.getNodesActuallyExpanded() << "):" << std::endl;
        std::cout << goal->getState()->toString();
    }
    return 0;
}
