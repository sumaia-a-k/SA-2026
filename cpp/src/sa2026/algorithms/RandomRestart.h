#pragma once

#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/SearchAlgorithm.h"

namespace sa2026::algorithms {

/*
 * Random-restart Hill Climbing.
 *
 * When Hill Climbing is stuck, start again from a NEW RANDOM state.
 * Repeat until we find a goal, or until we have done maxClimbs climbs.
 * (maxClimbs is a limit, so the search always stops.)
 *
 * The problem must be able to make a random start state (Problem::getRandomState),
 * for example 8-queens. On the city map the start is always S, so it does not help there.
 *
 * The counters (generated, expanded) count ALL the climbs together.
 * The same seed always gives the same random boards.
 */
class RandomRestart : public core::SearchAlgorithm {
public:
    RandomRestart(int maxClimbs, unsigned int seed);

    // how many climbs the last search did
    int getClimbs() const;

    core::NodePtr search(const core::Problem& p) override;

private:
    const int maxClimbs;
    const unsigned int seed;
    int climbs = 0;
};

}  // namespace sa2026::algorithms
