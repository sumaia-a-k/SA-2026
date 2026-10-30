#include "sa2026/algorithms/BFSOptimized.h"

#include <memory>
#include <queue>
#include <vector>

namespace sa2026::algorithms {

BFSOptimized::BFSOptimized() : SearchAlgorithm(false) {}

BFSOptimized::BFSOptimized(bool useGraphSearch) : SearchAlgorithm(useGraphSearch) {}

core::NodePtr BFSOptimized::search(const core::Problem& p) {
    resetCounters();

    std::queue<core::NodePtr> frontier;
    core::StateSet reached;  // every state we generated: in the queue or expanded
    int visitingOrder = 0;

    core::NodePtr startNode = std::make_shared<core::Node>(p.getInitialState());
    frontier.push(startNode);
    generatedNodes++;
    if (useGraphSearch) {
        reached.insert(startNode->getState());
    }

    while (!frontier.empty()) {
        core::NodePtr currentNode = frontier.front();
        frontier.pop();
        currentNode->setVisitingOrder(++visitingOrder);

        if (p.isGoal(currentNode->getState())) {
            return currentNode;
        }

        nodesActuallyExpanded++;
        for (const core::ActionPtr& action : p.getActions()) {
            std::vector<core::StatePtr> nextStates = action->apply(currentNode->getState());
            for (const core::StatePtr& s : nextStates) {
                // the change: we saw this state before, so do not add it again
                if (useGraphSearch && reached.count(s) > 0) {
                    continue;
                }
                if (useGraphSearch) {
                    reached.insert(s);
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

}  // namespace sa2026::algorithms
