#pragma once

#include "sa2026/core/State.h"

namespace sa2026::core {

/*
 * A heuristic is a guess of the cost from a state to the goal.
 * It is used by informed algorithms like Greedy and A*.
 */
class HeuristicFunction {
public:
    virtual ~HeuristicFunction() = default;

    // returns h(n): the guessed cost from state s to the goal
    virtual double getH(const StatePtr& s) const = 0;
};

}  // namespace sa2026::core
