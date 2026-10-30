#pragma once

#include <vector>

#include "sa2026/core/IAction.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/State.h"

namespace sa2026::problems::incomplete_code::npuzzle {

/*
 * STUDENT TASK: write the bodies in NpuzzleProblem.cpp.
 * This header is ready. Search for "TODO" in the .cpp file and follow the steps.
 *
 * The N-puzzle problem (8-puzzle, 15-puzzle, ...): slide the tiles until they are in order.
 *
 * Initial state: the board we get (0 = the empty cell).
 * Goal:          1, 2, 3, ..., n*n-1 and the empty cell at the end.
 * Actions:       move the empty cell up, down, left, right.
 * Cost:          every move costs 1.
 *
 * There is no heuristic yet. We add it in a later session (the 2025 code had the Hamming distance).
 *
 * What we fixed from the 2025 code:
 *  - The start board is checked: it must be n x n, have every number 0 .. n*n-1 once,
 *    and it must be solvable. (A random shuffle makes a board with NO solution half of the time,
 *    and then the search looks at every reachable state before it says "no solution".)
 */
class NpuzzleProblem : public core::Problem {
public:
    /*
     * Give the tiles row by row in { }, for example  NpuzzleProblem({4, 1, 2, 5, 8, 3, 7, 6, 0})
     * Throws std::invalid_argument if the board is wrong or can not be solved.
     */
    explicit NpuzzleProblem(const std::vector<int>& tiles);

    // the three tests from the 2025 code
    static NpuzzleProblem easy();    // 2 moves
    static NpuzzleProblem medium();  // 8 moves
    static NpuzzleProblem hard();    // 19 moves

    /*
     * Can this board reach the goal? Only HALF of all boards can.
     * Read the tiles row by row, skip the 0, and count the "inversions":
     * the pairs where a bigger number comes before a smaller one.
     *   n odd  (3 x 3): solvable if the number of inversions is even.
     *   n even (4 x 4): solvable if inversions + (the row of the empty cell,
     *                   counted from the bottom: 1, 2, 3, ...) is odd.
     */
    static bool isSolvable(const std::vector<int>& tiles);

    core::StatePtr getInitialState() const override;
    bool isGoal(const core::StatePtr& state) const override;
    std::vector<core::ActionPtr> getActions() const override;
    double getActionCost(const core::StatePtr& s, const core::ActionPtr& a,
                         const core::StatePtr& next) const override;

private:
    // checks the start board and throws an error with a clear message if it is wrong
    static void check(const std::vector<int>& tiles);

    core::StatePtr initialState;
    std::vector<core::ActionPtr> actions;
};

}  // namespace sa2026::problems::incomplete_code::npuzzle
