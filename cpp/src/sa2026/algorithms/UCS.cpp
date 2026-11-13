#include "sa2026/algorithms/UCS.h"

#include <memory>
#include <queue>
#include <vector>

namespace sa2026::algorithms {

UCS::UCS() : SearchAlgorithm(false) {}

UCS::UCS(bool useGraphSearch) : SearchAlgorithm(useGraphSearch) {}

core::NodePtr UCS::search(const core::Problem& p) {
    resetCounters();

    // std::priority_queue<item, the list inside, the rule>: top() is always the cheapest node.
    // For UCS, totalCost = pathCost = g(n) (see the Node constructors).
    std::priority_queue<core::NodePtr, std::vector<core::NodePtr>, CheaperFirst> frontier;
    core::StateSet explored;  // a hash set: count() is fast
    int visitingOrder = 0;

    core::NodePtr startNode = std::make_shared<core::Node>(p.getInitialState());
    frontier.push(startNode);
    generatedNodes++;  // the start node is a generated node too

    while (!frontier.empty()) {
        // take the cheapest node (the smallest path cost)
        core::NodePtr currentNode = frontier.top();
        frontier.pop();

        // graph search: the same state can be in the queue more than once
        // (with different costs). The cheapest copy comes out first,
        // so skip the other copies if we expanded this state before.
        if (useGraphSearch && explored.count(currentNode->getState()) > 0) {
            continue;
        }

        currentNode->setVisitingOrder(++visitingOrder);

        // goal test when we take the node out of the queue.
        // In UCS this is VERY important: a goal we only generated
        // may still have a cheaper path that we did not find yet.
        if (p.isGoal(currentNode->getState())) {
            return currentNode;
        }

        if (useGraphSearch) {
            explored.insert(currentNode->getState());
        }

        // expand: apply every action and add the children to the priority queue
        nodesActuallyExpanded++;
        for (const core::ActionPtr& action : p.getActions()) {
            std::vector<core::StatePtr> nextStates = action->apply(currentNode->getState());
            for (const core::StatePtr& s : nextStates) {
                double pathCost = currentNode->getPathCost()
                                  + p.getActionCost(currentNode->getState(), action, s);
                core::NodePtr child = std::make_shared<core::Node>(s, currentNode, action, pathCost);
                frontier.push(child);  // the queue puts it in the right place (by cost)
                generatedNodes++;
            }
        }
    }

    // the queue is empty and we did not find a goal
    return nullptr;
}

}  // namespace sa2026::algorithms
