#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "sa2026/algorithms/HillClimbing.h"
#include "sa2026/algorithms/incomplete_code/HillClimbing.h"
#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"
#include "sa2026/problems/citymap/CityHeuristic.h"
#include "sa2026/problems/citymap/CityMap.h"
#include "sa2026/problems/citymap/CityMapProblem.h"
#include "sa2026/problems/maze/Maze.h"
#include "sa2026/problems/maze/MazeProblem.h"
#include "sa2026/problems/npuzzle/NpuzzleProblem.h"
#include "sa2026/problems/queens/QueensProblem.h"

// "HillClimbing" is your class (this folder). The finished one is finished::HillClimbing
using sa2026::algorithms::incomplete_code::HillClimbing;
namespace finished = sa2026::algorithms;  // a short name for a namespace

using sa2026::core::Node;
using sa2026::core::NodePtr;
using sa2026::core::Problem;
using sa2026::problems::citymap::CityHeuristic;
using sa2026::problems::citymap::CityMap;
using sa2026::problems::citymap::CityMapProblem;
using sa2026::problems::maze::Maze;
using sa2026::problems::maze::MazeProblem;
using sa2026::problems::npuzzle::NpuzzleProblem;
using sa2026::problems::queens::QueensProblem;

/*
 * Checks YOUR HillClimbing (in this folder) with the finished one (in sa2026::algorithms).
 * Both solve the same problems. The answers and the numbers must be the same.
 *
 * How to run (inside the SA-2026/cpp folder, NOT its parent folder):
 *   .\run.bat sa2026.algorithms.incomplete_code.HillClimbingDemo   (Windows)
 *   ./run.sh sa2026.algorithms.incomplete_code.HillClimbingDemo    (Git Bash, macOS, Linux)
 *
 * Some checks get STUCK (no goal): your search must return nullptr there too,
 * and getStuckNode() must give the same state.
 * If the program does not stop, your loop never ends (for example: you move when
 * the best neighbour has the SAME h). Stop it with Ctrl+C.
 */

// the "misleading guess" of the lesson pages. The goal is G.
static std::shared_ptr<CityHeuristic> misleadingGuessToG() {
    return std::make_shared<CityHeuristic>(std::map<std::string, int>{
            {"S", 9}, {"A", 2}, {"B", 6}, {"C", 1}, {"D", 7}, {"E", 5}, {"F", 6}, {"G", 0}});
}

// true if the two paths have the same states, in the same order
static bool samePath(const NodePtr& a, const NodePtr& b) {
    std::vector<const Node*> pathA = a->getPathFromRoot();
    std::vector<const Node*> pathB = b->getPathFromRoot();
    if (pathA.size() != pathB.size()) return false;
    for (std::size_t i = 0; i < pathA.size(); i++) {
        if (!pathA[i]->getState()->equals(*pathB[i]->getState())) return false;
    }
    return true;
}

// returns an empty text if the results are the same, or a text that says what is different
static std::string compare(const NodePtr& yourGoal, const NodePtr& goal,
                           const HillClimbing& yours, const finished::HillClimbing& finishedOne) {
    if (goal == nullptr && yourGoal != nullptr) {
        return "you found a goal, but Hill Climbing gets stuck here";
    }
    if (goal != nullptr && yourGoal == nullptr) {
        return "your search returned nullptr (stuck), but Hill Climbing finds the goal here";
    }
    // the node where the climb ended: the goal, or the stuck node
    NodePtr yourEnd = (yourGoal != nullptr) ? yourGoal : yours.getStuckNode();
    NodePtr end = (goal != nullptr) ? goal : finishedOne.getStuckNode();
    if (yourEnd == nullptr) {
        return "you are stuck, but getStuckNode() is nullptr (set stuckNode before you return nullptr)";
    }
    if (!samePath(yourEnd, end)) {
        return "your path is not the same (moves: " + std::to_string(yourEnd->getDepth())
               + ", it should be " + std::to_string(end->getDepth()) + ")";
    }
    if (yours.getNodesActuallyExpanded() != finishedOne.getNodesActuallyExpanded()) {
        return "expanded nodes = " + std::to_string(yours.getNodesActuallyExpanded())
               + ", it should be " + std::to_string(finishedOne.getNodesActuallyExpanded());
    }
    if (yours.getGeneratedNodes() != finishedOne.getGeneratedNodes()) {
        return "generated nodes = " + std::to_string(yours.getGeneratedNodes())
               + ", it should be " + std::to_string(finishedOne.getGeneratedNodes());
    }
    return "";
}

// prints OK or NOT YET; returns 1 if it is OK
static int report(const std::string& problemText) {
    if (problemText.empty()) {
        std::cout << "OK" << std::endl;
        return 1;
    }
    std::cout << "NOT YET: " << problemText << std::endl;
    return 0;
}

// solves the problem with your HillClimbing and the finished one and compares the results;
// returns 1 if they are the same
static int check(const std::string& name, const Problem& problem) {
    // print it first: if your search never ends, you see where.
    // std::flush = show it now (normally the text waits until the end of the line)
    std::cout << "Checking " << name << " ... " << std::flush;
    HillClimbing yours;
    finished::HillClimbing finishedOne;
    NodePtr yourGoal = problem.solve(yours);
    NodePtr goal = problem.solve(finishedOne);
    return report(compare(yourGoal, goal, yours, finishedOne));
}

int main() {
    CityMap map = CityMap::example();
    int ok = 0;

    // CityState keeps only ONE goal city (a static field), so a new CityMapProblem
    // changes the goal of the old one too. We make each problem only when we need it.
    {   // { } = a block: gps is deleted at the end of the block
        CityMapProblem gps("S", "G", map, std::make_shared<CityHeuristic>(CityHeuristic::gpsGuessToG()));
        ok += check("city map, GPS guess", gps);
    }
    {
        CityMapProblem misleading("S", "G", map, misleadingGuessToG());
        ok += check("city map, misleading guess", misleading);
    }

    // the maze uses the Manhattan distance as its guess
    MazeProblem maze(Maze::fromLines({
            "S.#....",
            ".##.##.",
            "....#..",
            ".##....",
            "...#.#G"}));
    ok += check("maze", maze);
    ok += check("8-puzzle (medium)", NpuzzleProblem::medium());
    ok += check("8-queens, Example 1", QueensProblem::example1());
    ok += check("8-queens, Example 2", QueensProblem::example2());

    std::cout << "\n" << ok << " of 6 checks are OK." << std::endl;
    return 0;
}
