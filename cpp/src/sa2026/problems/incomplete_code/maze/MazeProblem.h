#pragma once

#include <vector>

#include "sa2026/core/IAction.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/State.h"
#include "sa2026/problems/incomplete_code/maze/Maze.h"

namespace sa2026::problems::incomplete_code::maze {

/*
 * STUDENT TASK: finish this class (in MazeProblem.cpp).
 *
 * The maze problem: move the player from the start cell to the goal cell.
 *
 * Initial state: the player is on 'S'.
 * Goal:          the player is on 'G'.
 * Actions:       move up, down, left, right (one cell, not into a wall).
 * Cost:          every move costs 1.
 *
 * There is no heuristic yet. We add it in a later session.
 *
 * Search for "TODO" and follow the steps.
 */
class MazeProblem : public core::Problem {
public:
    explicit MazeProblem(const MazePtr& maze);

    core::StatePtr getInitialState() const override;
    bool isGoal(const core::StatePtr& state) const override;
    std::vector<core::ActionPtr> getActions() const override;
    double getActionCost(const core::StatePtr& s, const core::ActionPtr& a,
                         const core::StatePtr& next) const override;

private:
    core::StatePtr initialState;
    std::vector<core::ActionPtr> actions;
};

}  // namespace sa2026::problems::incomplete_code::maze
