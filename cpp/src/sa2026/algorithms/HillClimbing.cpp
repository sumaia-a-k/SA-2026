#include "sa2026/algorithms/HillClimbing.h"

#include <memory>
#include <vector>

#include "sa2026/core/HeuristicFunction.h"

namespace sa2026::algorithms {

HillClimbing::HillClimbing() {}

core::NodePtr HillClimbing::getStuckNode() const {
    return stuckNode;
}

core::NodePtr HillClimbing::search(const core::Problem& p) {
    resetCounters();
    return climb(p, p.getInitialState());
}

core::NodePtr HillClimbing::climb(const core::Problem& p, const core::StatePtr& start) {
    stuckNode = nullptr;
    std::shared_ptr<const core::HeuristicFunction> h = p.getHeuristicFunction();
    int visitingOrder = 0;

    // the start node: path cost 0, totalCost = h(start)
    core::NodePtr current = std::make_shared<core::Node>(start, nullptr, nullptr, 0.0, h->getH(start));
    generatedNodes++;

    while (true) {
        current->setVisitingOrder(++visitingOrder);

        // goal test first
        if (p.isGoal(current->getState())) {
            return current;
        }

        // look at ALL the neighbours and keep the best one
        nodesActuallyExpanded++;
        core::NodePtr best = nullptr;
        for (const core::ActionPtr& action : p.getActions()) {
            std::vector<core::StatePtr> nextStates = action->apply(current->getState());
            for (const core::StatePtr& s : nextStates) {
                double pathCost = current->getPathCost() + p.getActionCost(current->getState(), action, s);
                core::NodePtr child = std::make_shared<core::Node>(s, current, action, pathCost, h->getH(s));
                generatedNodes++;
                // "<" and not "<=": a later neighbour with the same h does not win
                if (best == nullptr || child->getTotalCost() < best->getTotalCost()) {
                    best = child;
                }
            }
        }

        // no neighbour is better (or there is no neighbour): stop, we are stuck
        if (best == nullptr || best->getTotalCost() >= current->getTotalCost()) {
            stuckNode = current;
            return nullptr;
        }
        current = best;
    }
}

}  // namespace sa2026::algorithms
