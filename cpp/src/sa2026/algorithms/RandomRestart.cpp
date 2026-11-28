#include "sa2026/algorithms/RandomRestart.h"

#include <random>  // std::mt19937
#include <stdexcept>
#include <string>

#include "sa2026/algorithms/HillClimbing.h"

namespace sa2026::algorithms {

RandomRestart::RandomRestart(int maxClimbs, unsigned int seed)
    : maxClimbs(maxClimbs), seed(seed) {
    if (maxClimbs < 1) {
        throw std::invalid_argument("maxClimbs must be 1 or more, not " + std::to_string(maxClimbs) + ".");
    }
}

int RandomRestart::getClimbs() const {
    return climbs;
}

core::NodePtr RandomRestart::search(const core::Problem& p) {
    resetCounters();
    climbs = 0;
    std::mt19937 random(seed);
    HillClimbing hill;  // its counters start at 0

    core::NodePtr goal = nullptr;
    while (climbs < maxClimbs && goal == nullptr) {
        core::StatePtr start = p.getRandomState(random);
        goal = hill.climb(p, start);
        climbs++;
    }

    // the numbers of all the climbs together
    generatedNodes = hill.getGeneratedNodes();
    nodesActuallyExpanded = hill.getNodesActuallyExpanded();
    return goal;  // nullptr: no goal after maxClimbs climbs
}

}  // namespace sa2026::algorithms
