#include "sa2026/algorithms/DepthLimitedDFS.h"

#include <memory>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

namespace sa2026::algorithms {

DepthLimitedDFS::DepthLimitedDFS(int limit) : SearchAlgorithm(false), limit(limit) {
    if (limit < 0) {
        throw std::invalid_argument("The limit must be 0 or more, not " + std::to_string(limit) + ".");
    }
}

bool DepthLimitedDFS::isCutoff() const {
    return cutoff;
}

core::NodePtr DepthLimitedDFS::search(const core::Problem& p) {
    resetCounters();
    cutoff = false;  // a new search: no cutoff yet

    std::stack<core::NodePtr> frontier;
    int visitingOrder = 0;

    core::NodePtr startNode = std::make_shared<core::Node>(p.getInitialState());
    frontier.push(startNode);
    generatedNodes++;

    while (!frontier.empty()) {
        core::NodePtr currentNode = frontier.top();
        frontier.pop();
        currentNode->setVisitingOrder(++visitingOrder);

        if (p.isGoal(currentNode->getState())) {
            return currentNode;
        }

        // do not go deeper than the limit
        if (currentNode->getDepth() >= limit) {
            cutoff = true;  // remember that it happened, nothing more
            continue;
        }

        nodesActuallyExpanded++;
        for (const core::ActionPtr& action : p.getActions()) {
            std::vector<core::StatePtr> nextStates = action->apply(currentNode->getState());
            for (const core::StatePtr& s : nextStates) {
                // cycle check: do not go back to a state on our own path
                if (isOnPath(currentNode, s)) {
                    continue;
                }
                double pathCost = currentNode->getPathCost()
                                  + p.getActionCost(currentNode->getState(), action, s);
                core::NodePtr child = std::make_shared<core::Node>(s, currentNode, action, pathCost);
                frontier.push(child);
                generatedNodes++;
            }
        }
    }

    return nullptr;
}

bool DepthLimitedDFS::isOnPath(const core::NodePtr& node, const core::StatePtr& s) {
    for (core::NodePtr n = node; n != nullptr; n = n->getParent()) {
        if (n->getState()->equals(*s)) {
            return true;
        }
    }
    return false;
}

}  // namespace sa2026::algorithms
