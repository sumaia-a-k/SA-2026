#include "sa2026/algorithms/incomplete_code/BFS.h"

#include <memory>  // you need them in the TODOs
#include <queue>
#include <vector>

namespace sa2026::algorithms::incomplete_code {

BFS::BFS() : SearchAlgorithm(false) {}

BFS::BFS(bool useGraphSearch) : SearchAlgorithm(useGraphSearch) {}

core::NodePtr BFS::search(const core::Problem& p) {
    resetCounters();

    // TODO 1: create the frontier, a queue of nodes:  std::queue<core::NodePtr> frontier;
    //         create the set of explored states:     core::StateSet explored;
    //         and a counter:                         int visitingOrder = 0;
    //         Question: why do we create them here, and not as fields of the class?

    // TODO 2: create the start node:  std::make_shared<core::Node>(p.getInitialState())
    //         and add it to the frontier (frontier.push(...)).
    //         The start node is a generated node too: generatedNodes++

    // TODO 3: while the frontier is not empty (!frontier.empty()):
    //   a) take the oldest node out of the queue. In C++ this needs two steps:
    //        core::NodePtr currentNode = frontier.front();   // read the first node
    //        frontier.pop();                                  // remove it
    //   b) graph search only (useGraphSearch is true):
    //      if explored.count(currentNode->getState()) > 0, skip it with "continue".
    //      Question: how can the same state be in the queue two times?
    //   c) currentNode->setVisitingOrder(++visitingOrder);
    //   d) goal test: if p.isGoal(currentNode->getState()), return currentNode.
    //      Question: why do we test the goal when we take the node OUT of the queue,
    //                and not when we put it in?
    //   e) graph search only: explored.insert(currentNode->getState());
    //   f) expand the node: nodesActuallyExpanded++
    //      then for every action in p.getActions()     (for (const core::ActionPtr& action : ...))
    //      and for every next state s in action->apply(currentNode->getState()):
    //        - double pathCost = currentNode->getPathCost() + p.getActionCost(currentNode->getState(), action, s);
    //        - core::NodePtr child = std::make_shared<core::Node>(s, currentNode, action, pathCost);
    //        - add the child to the END of the queue (push), and count it: generatedNodes++

    // TODO 4: the queue is empty and we did not find a goal: return nullptr.
    return nullptr;
}

}  // namespace sa2026::algorithms::incomplete_code
