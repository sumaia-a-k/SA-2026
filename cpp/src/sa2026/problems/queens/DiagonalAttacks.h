#pragma once

#include "sa2026/core/HeuristicFunction.h"
#include "sa2026/core/State.h"

namespace sa2026::problems::queens {

/*
 * h = the number of pairs of queens on the same diagonal.
 * The goal has h = 0. Smaller is better, so Hill Climbing goes down to 0.
 */
class DiagonalAttacks : public core::HeuristicFunction {
public:
    double getH(const core::StatePtr& s) const override;
};

}  // namespace sa2026::problems::queens
