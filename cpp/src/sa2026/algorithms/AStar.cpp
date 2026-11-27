#include "sa2026/algorithms/AStar.h"

#include <memory>
#include <queue>
#include <vector>

#include "sa2026/core/HeuristicFunction.h"

namespace sa2026::algorithms {

AStar::AStar() : SearchAlgorithm(false) {}

AStar::AStar(bool useGraphSearch) : SearchAlgorithm(useGraphSearch) {}

core::NodePtr AStar::search(const core::Problem& p) {
    resetCounters();

    // the guess h(n) of this problem (throws an error if the problem has no heuristic)
    std::shared_ptr<const core::HeuristicFunction> h = p.getHeuristicFunction();

    // top() is always the node with the smallest totalCost.
    // Here totalCost = f(n), and we give it to the Node constructor ourselves.
    std::priority_queue<core::NodePtr, std::vector<core::NodePtr>, CheaperFirst> frontier;
    core::StateSet explored;  // a hash set: count() is fast
    int visitingOrder = 0;

    // the start node: path cost 0, f(n) = 0 + h(n)
    core::StatePtr start = p.getInitialState();
    core::NodePtr startNode = std::make_shared<core::Node>(start, nullptr, nullptr, 0.0, h->getH(start));
    frontier.push(startNode);
    generatedNodes++;  // the start node is a generated node too

    while (!frontier.empty()) {
        // take the node with the smallest f(n)
        core::NodePtr currentNode = frontier.top();
        frontier.pop();

        // graph search: skip the other copies of a state we already expanded
        if (useGraphSearch && explored.count(currentNode->getState()) > 0) {
            continue;
        }

        currentNode->setVisitingOrder(++visitingOrder);

        // goal test when we take the node out of the queue. In A* this is a MUST (like UCS):
        // a goal we only generated may still have a cheaper path.
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
                // g(n): the real cost from the start
                double pathCost = currentNode->getPathCost()
                                  + p.getActionCost(currentNode->getState(), action, s);
                // f(n) = g(n) + h(n): the real cost so far + the guess to the goal
                double f = pathCost + h->getH(s);
                core::NodePtr child = std::make_shared<core::Node>(s, currentNode, action, pathCost, f);
                frontier.push(child);  // the queue puts it in the right place (by f)
                generatedNodes++;
            }
        }
    }

    // the queue is empty and we did not find a goal
    return nullptr;
}

}  // namespace sa2026::algorithms
