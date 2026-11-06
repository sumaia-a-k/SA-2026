#include "sa2026/algorithms/DFSCycleCheck.h"

#include <memory>
#include <stack>
#include <vector>

namespace sa2026::algorithms {

DFSCycleCheck::DFSCycleCheck() : SearchAlgorithm(false) {}

core::NodePtr DFSCycleCheck::search(const core::Problem& p) {
    resetCounters();

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

        nodesActuallyExpanded++;
        for (const core::ActionPtr& action : p.getActions()) {
            std::vector<core::StatePtr> nextStates = action->apply(currentNode->getState());
            for (const core::StatePtr& s : nextStates) {
                // the change: s is already on our path, so it is a cycle
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

bool DFSCycleCheck::isOnPath(const core::NodePtr& node, const core::StatePtr& s) {
    for (core::NodePtr n = node; n != nullptr; n = n->getParent()) {
        if (n->getState()->equals(*s)) {
            return true;
        }
    }
    return false;
}

}  // namespace sa2026::algorithms
