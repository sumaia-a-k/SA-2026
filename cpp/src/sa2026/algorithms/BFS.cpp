#include "sa2026/algorithms/BFS.h"

#include <memory>
#include <queue>
#include <vector>

namespace sa2026::algorithms {

BFS::BFS() : SearchAlgorithm(false) {}

BFS::BFS(bool useGraphSearch) : SearchAlgorithm(useGraphSearch) {}

core::NodePtr BFS::search(const core::Problem& p) {
    resetCounters();

    // We create these here and not as fields,
    // so every new search starts with an empty queue.
    // std::queue: push() adds at the end, front() reads the first one, pop() removes it.
    std::queue<core::NodePtr> frontier;
    core::StateSet explored;  // a hash set: count() is fast
    int visitingOrder = 0;

    core::NodePtr startNode = std::make_shared<core::Node>(p.getInitialState());
    frontier.push(startNode);
    generatedNodes++;  // the start node is a generated node too

    while (!frontier.empty()) {
        // take the oldest node (the first one in the queue)
        core::NodePtr currentNode = frontier.front();
        frontier.pop();

        // graph search: the same state can be in the queue more than once,
        // so skip it if we expanded it before
        if (useGraphSearch && explored.count(currentNode->getState()) > 0) {
            continue;
        }

        currentNode->setVisitingOrder(++visitingOrder);

        // goal test when we take the node out of the queue
        if (p.isGoal(currentNode->getState())) {
            return currentNode;
        }

        if (useGraphSearch) {
            explored.insert(currentNode->getState());
        }

        // expand: apply every action and add the children to the end of the queue
        nodesActuallyExpanded++;
        for (const core::ActionPtr& action : p.getActions()) {
            std::vector<core::StatePtr> nextStates = action->apply(currentNode->getState());
            for (const core::StatePtr& s : nextStates) {
                double pathCost = currentNode->getPathCost()
                                  + p.getActionCost(currentNode->getState(), action, s);
                core::NodePtr child = std::make_shared<core::Node>(s, currentNode, action, pathCost);
                frontier.push(child);
                generatedNodes++;
            }
        }
    }

    // the queue is empty and we did not find a goal
    return nullptr;
}

}  // namespace sa2026::algorithms
