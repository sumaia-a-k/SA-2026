#pragma once

#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/SearchAlgorithm.h"

namespace sa2026::algorithms {

/*
 * Stochastic Hill Climbing.
 *
 * The same as HillClimbing, but it does not take the BEST neighbour:
 * it takes a RANDOM one of the BETTER neighbours (h(neighbour) < h(current)).
 * Every better neighbour has the same chance.
 * It stops for the same reason: no neighbour is better.
 *
 * It usually needs more moves. Two runs with different seeds can end in different places.
 * The same seed always gives the same result. (Java and Python have other random makers,
 * so there the same seed can give another result.)
 */
class StochasticHillClimbing : public core::SearchAlgorithm {
public:
    explicit StochasticHillClimbing(unsigned int seed);

    // the node where the last search stopped without a goal (nullptr after a success)
    core::NodePtr getStuckNode() const;

    core::NodePtr search(const core::Problem& p) override;

private:
    const unsigned int seed;
    core::NodePtr stuckNode;  // where the last search stopped, when it did not find a goal
};

}  // namespace sa2026::algorithms
