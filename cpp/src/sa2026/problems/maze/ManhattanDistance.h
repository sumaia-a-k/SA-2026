#pragma once

#include "sa2026/core/HeuristicFunction.h"
#include "sa2026/core/State.h"

namespace sa2026::problems::maze {

/*
 * The Manhattan distance from the player to the goal: |row - goalRow| + |col - goalCol|.
 *
 * It is the number of steps when there are no walls. Every step moves one cell,
 * up, down, left or right, so we need AT LEAST this number of steps.
 * The real path can only be longer (walls), never shorter.
 * So this guess is admissible. It is also consistent: one step changes it by 1 at most.
 */
class ManhattanDistance : public core::HeuristicFunction {
public:
    double getH(const core::StatePtr& s) const override;
};

}  // namespace sa2026::problems::maze
