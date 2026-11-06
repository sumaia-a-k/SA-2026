#include "sa2026/algorithms/DFS.h"

#include <memory>
#include <stack>
#include <vector>

namespace sa2026::algorithms {

DFS::DFS() : SearchAlgorithm(false) {}

DFS::DFS(bool useGraphSearch) : SearchAlgorithm(useGraphSearch) {}

core::NodePtr DFS::search(const core::Problem& p) {
    resetCounters();

    // std::stack: push() puts a node on the top, top() reads it, pop() removes it.
    std::stack<core::NodePtr> frontier;
    core::StateSet explored;  // a hash set: count() is fast
    int visitingOrder = 0;

    core::NodePtr startNode = std::make_shared<core::Node>(p.getInitialState());
    frontier.push(startNode);
    generatedNodes++;  // the start node is a generated node too

    while (!frontier.empty()) {
        // take the newest node (the top of the stack)
        core::NodePtr currentNode = frontier.top();
        frontier.pop();

        // graph search: the same state can be in the stack more than once,
        // so skip it if we expanded it before
        if (useGraphSearch && explored.count(currentNode->getState()) > 0) {
            continue;
        }

        currentNode->setVisitingOrder(++visitingOrder);

        // goal test when we take the node out of the stack
        if (p.isGoal(currentNode->getState())) {
            return currentNode;
        }

        if (useGraphSearch) {
            explored.insert(currentNode->getState());
        }

        // expand: apply every action and push the children on the top.
        // The last child we push is the first one we take.
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

    // the stack is empty and we did not find a goal
    return nullptr;
}

}  // namespace sa2026::algorithms
