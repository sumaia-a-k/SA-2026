#pragma once

#include <string>
#include <vector>

#include "sa2026/core/IAction.h"
#include "sa2026/core/State.h"

namespace sa2026::problems::incomplete_code::npuzzle {

/*
 * STUDENT TASK: write the bodies in MoveEmptyAction.cpp.
 * This header is ready. Search for "TODO" in the .cpp file and follow the steps.
 *
 * One action of the N-puzzle: move the EMPTY cell up, down, left or right.
 * It is the same move as "the tile next to it slides the other way",
 * but now there are only 4 actions (not 8 tiles x 4 directions).
 *
 * Like MazeAction: one class, and four objects with different directions (see NpuzzleProblem):
 *   ActionPtr up = std::make_shared<MoveEmptyAction>("Move empty up", -1, 0);
 * (The 2025 code had four classes, MoveEmptyTileUp, ..., with almost the same code.)
 */
class MoveEmptyAction : public core::IAction {
public:
    MoveEmptyAction(const std::string& name, int rowChange, int colChange);

    // moves the empty cell one step; returns no state if it would go outside the board
    std::vector<core::StatePtr> apply(const core::StatePtr& s) const override;

    std::string getName() const override;

private:
    const std::string name;
    const int rowChange;  // how much the row of the empty cell changes: -1, 0 or +1
    const int colChange;  // how much the col of the empty cell changes: -1, 0 or +1
};

}  // namespace sa2026::problems::incomplete_code::npuzzle
