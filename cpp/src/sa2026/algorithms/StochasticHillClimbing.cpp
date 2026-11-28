#include "sa2026/algorithms/StochasticHillClimbing.h"

#include <memory>
#include <random>  // std::mt19937, std::uniform_int_distribution
#include <vector>

#include "sa2026/core/HeuristicFunction.h"

namespace sa2026::algorithms {

StochasticHillClimbing::StochasticHillClimbing(unsigned int seed) : seed(seed) {}

core::NodePtr StochasticHillClimbing::getStuckNode() const {
    return stuckNode;
}

core::NodePtr StochasticHillClimbing::search(const core::Problem& p) {
    resetCounters();
    stuckNode = nullptr;
    // a new search with the same seed makes the same random choices again
    std::mt19937 random(seed);
    std::shared_ptr<const core::HeuristicFunction> h = p.getHeuristicFunction();
    int visitingOrder = 0;

    core::StatePtr start = p.getInitialState();
    core::NodePtr current = std::make_shared<core::Node>(start, nullptr, nullptr, 0.0, h->getH(start));
    generatedNodes++;

    while (true) {
        current->setVisitingOrder(++visitingOrder);
        if (p.isGoal(current->getState())) {
            return current;
        }

        // keep ALL the better neighbours (not only the best one)
        nodesActuallyExpanded++;
        std::vector<core::NodePtr> better;
        for (const core::ActionPtr& action : p.getActions()) {
            std::vector<core::StatePtr> nextStates = action->apply(current->getState());
            for (const core::StatePtr& s : nextStates) {
                double pathCost = current->getPathCost() + p.getActionCost(current->getState(), action, s);
                core::NodePtr child = std::make_shared<core::Node>(s, current, action, pathCost, h->getH(s));
                generatedNodes++;
                if (child->getTotalCost() < current->getTotalCost()) {
                    better.push_back(child);
                }
            }
        }

        // no neighbour is better: stop, we are stuck
        if (better.empty()) {
            stuckNode = current;
            return nullptr;
        }
        // take a random one of the better neighbours: a random place from 0 to better.size() - 1
        std::uniform_int_distribution<int> pick(0, static_cast<int>(better.size()) - 1);
        current = better[pick(random)];
    }
}

}  // namespace sa2026::algorithms
