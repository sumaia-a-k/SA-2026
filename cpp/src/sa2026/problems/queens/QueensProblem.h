#pragma once

#include <memory>
#include <random>  // std::mt19937
#include <vector>

#include "sa2026/core/HeuristicFunction.h"
#include "sa2026/core/IAction.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/State.h"

namespace sa2026::problems::queens {

/*
 * The 8-queens problem: put 8 queens on a chess board so that no two attack each other.
 * (A queen attacks along its row, its column and its two diagonals.)
 *
 * Initial state: a board with one queen in every row and every column (see QueensState).
 * Goal:          no two queens on the same diagonal (h = 0).
 * Actions:       swap two queens (28 neighbours).
 * Cost:          every swap costs 1. (We do not care about the path, only about the final board.)
 * Heuristic:     DiagonalAttacks: the number of pairs of queens on the same diagonal.
 *
 * This problem is for local search (Hill Climbing). It can also make a random start state
 * (getRandomState), so RandomRestart can use it.
 */
class QueensProblem : public core::Problem {
public:
    /*
     * Give the row of the queen of each column in { }, for example
     *   QueensProblem({0, 1, 3, 4, 5, 2, 7, 6})
     * Every row from 0 to n-1 must be used once (one queen in every row).
     * Throws std::invalid_argument if the board is wrong.
     */
    explicit QueensProblem(const std::vector<int>& rows);

    // Example 1 of the lesson page: h = 9, Hill Climbing solves it in 3 swaps
    static QueensProblem example1();

    // Example 2 of the lesson page: h = 9, Hill Climbing gets stuck at h = 1 (a flat place)
    static QueensProblem example2();

    core::StatePtr getInitialState() const override;
    bool isGoal(const core::StatePtr& state) const override;
    std::vector<core::ActionPtr> getActions() const override;
    double getActionCost(const core::StatePtr& s, const core::ActionPtr& a,
                         const core::StatePtr& next) const override;
    std::shared_ptr<const core::HeuristicFunction> getHeuristicFunction() const override;

    // a random board of the same size: the rows 0, 1, ..., n-1 in a random order
    core::StatePtr getRandomState(std::mt19937& random) const override;

private:
    // checks the board and throws an error with a clear message if it is wrong
    static void check(const std::vector<int>& rows);

    core::StatePtr initialState;
    int size;  // the board is size x size
    std::vector<core::ActionPtr> actions;
    std::shared_ptr<const core::HeuristicFunction> heuristic;
};

}  // namespace sa2026::problems::queens
