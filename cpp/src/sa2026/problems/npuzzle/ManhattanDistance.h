#pragma once

#include "sa2026/core/HeuristicFunction.h"
#include "sa2026/core/State.h"

namespace sa2026::problems::npuzzle {

/*
 * h2 = the sum of the Manhattan distances of all tiles to their goal place
 * (the empty cell is not counted).
 *
 * One move slides one tile one cell, so a tile needs AT LEAST its distance in moves.
 * The guess is admissible (and consistent).
 * It is never smaller than h1 (MisplacedTiles), so it helps A* more: fewer nodes.
 */
class ManhattanDistance : public core::HeuristicFunction {
public:
    double getH(const core::StatePtr& s) const override;
};

}  // namespace sa2026::problems::npuzzle
