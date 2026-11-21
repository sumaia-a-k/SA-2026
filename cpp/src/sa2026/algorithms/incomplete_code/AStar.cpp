#include "sa2026/algorithms/incomplete_code/AStar.h"

#include <memory>  // you need them in the TODOs
#include <queue>
#include <vector>

#include "sa2026/core/HeuristicFunction.h"

namespace sa2026::algorithms::incomplete_code {

AStar::AStar() : SearchAlgorithm(false) {}

AStar::AStar(bool useGraphSearch) : SearchAlgorithm(useGraphSearch) {}

core::NodePtr AStar::search(const core::Problem& p) {
    resetCounters();

    // The code is almost the same as your UCS.cpp (and your Greedy.cpp).
    // Only f(n), the number the queue sorts by, is different.

    // TODO 1: get the heuristic of the problem:
    //           std::shared_ptr<const core::HeuristicFunction> h = p.getHeuristicFunction();
    //         Then, like in UCS: the frontier with our rule CheaperFirst (in AStar.h):
    //           std::priority_queue<core::NodePtr, std::vector<core::NodePtr>, CheaperFirst> frontier;
    //         core::StateSet explored;  and  int visitingOrder = 0;

    // TODO 2: create the start node with FIVE values:
    //           std::make_shared<core::Node>(start, nullptr, nullptr, 0.0, f)
    //         (start = p.getInitialState()). Add it to the frontier and count it: generatedNodes++
    //         Question: what is f(n) of the start node? (g = 0)

    // TODO 3: while the frontier is not empty (!frontier.empty()):
    //   a) take the node with the smallest f(n), in two steps (like UCS):
    //        core::NodePtr currentNode = frontier.top();
    //        frontier.pop();
    //   b) graph search only: if explored.count(currentNode->getState()) > 0, skip it with "continue".
    //   c) currentNode->setVisitingOrder(++visitingOrder);
    //   d) goal test: if p.isGoal(currentNode->getState()), return currentNode.
    //      Question: why must we test the goal here, and not when we create the child?
    //   e) graph search only: explored.insert(currentNode->getState());
    //   f) expand the node: nodesActuallyExpanded++
    //      then for every action and every next state s (like in UCS):
    //        - double pathCost = currentNode->getPathCost() + p.getActionCost(currentNode->getState(), action, s);
    //        - double f = pathCost + h->getH(s);   <- the only line that makes it A*
    //        - core::NodePtr child = std::make_shared<core::Node>(s, currentNode, action, pathCost, f);
    //        - frontier.push(child);  and count it: generatedNodes++
    //   Question: what happens if h->getH(s) is 0 for every state? (AStarDemo has a check for it.)

    // TODO 4: the queue is empty and we did not find a goal: return nullptr.
    //   Question: on the "small map" in AStarDemo, graph search returns a path of 9 km,
    //             but tree search finds 7 km. The guess is admissible. Why is it not enough?
    return nullptr;
}

}  // namespace sa2026::algorithms::incomplete_code
