#include <cstdio>
#include <iostream>
#include <string>

#include "sa2026/algorithms/BFS.h"
#include "sa2026/algorithms/BFSOptimized.h"
#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/SearchAlgorithm.h"
#include "sa2026/problems/maze/Maze.h"
#include "sa2026/problems/maze/MazeProblem.h"

// "using" lets us write BFS instead of sa2026::algorithms::BFS (like import in Java)
using sa2026::algorithms::BFS;
using sa2026::algorithms::BFSOptimized;
using sa2026::core::NodePtr;
using sa2026::core::Problem;
using sa2026::core::SearchAlgorithm;
using sa2026::problems::maze::Maze;
using sa2026::problems::maze::MazePtr;
using sa2026::problems::maze::MazeProblem;

/*
 * The start point of the program.
 * We solve the maze with BFS, then we compare the BFS versions.
 *
 * How to run (inside the SA-2026/cpp folder):
 *   .\run.bat   (Windows)   or   ./run.sh   (Git Bash, macOS, Linux)
 */

// solves the problem and prints one line of numbers
// (in C++ a function must be written before we use it, so it comes before main)
static void compare(const std::string& name, SearchAlgorithm& algorithm, const Problem& problem) {
    NodePtr goal = problem.solve(algorithm);
    int steps = (goal == nullptr) ? -1 : goal->getDepth();
    // std::printf works like System.out.printf in Java. c_str() gives the text in the old C form.
    std::printf("%-24s %5d %9d %10d\n", name.c_str(), steps,
                algorithm.getNodesActuallyExpanded(), algorithm.getGeneratedNodes());
}

int main() {
    MazePtr maze = Maze::fromLines({
            "S.#....",
            ".##.##.",
            "....#..",
            ".##....",
            "...#.#G"});
    MazeProblem problem(maze);

    // 1. solve the maze with BFS (graph search) and print every step
    std::cout << "=== BFS, graph search ===" << std::endl;
    BFS algorithm(true);
    NodePtr goal = problem.solve(algorithm);
    algorithm.printSolution(goal);

    // 2. the same maze with every version, to compare the numbers
    std::cout << "\n=== Compare the BFS versions ===" << std::endl;
    std::cout << "Version                  Steps  Expanded  Generated" << std::endl;
    BFS treeSearch(false);
    BFS graphSearch(true);
    BFSOptimized optimized(true);
    compare("BFS, tree search", treeSearch, problem);
    compare("BFS, graph search", graphSearch, problem);
    compare("BFSOptimized, graph", optimized, problem);
    return 0;
}
