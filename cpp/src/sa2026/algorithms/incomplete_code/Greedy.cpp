#include "sa2026/algorithms/incomplete_code/Greedy.h"

#include <memory>  // you need them in the TODOs
#include <queue>
#include <vector>

#include "sa2026/core/HeuristicFunction.h"

namespace sa2026::algorithms::incomplete_code {

Greedy::Greedy() : SearchAlgorithm(false) {}

Greedy::Greedy(bool useGraphSearch) : SearchAlgorithm(useGraphSearch) {}

core::NodePtr Greedy::search(const core::Problem& p) {
    resetCounters();

    // The code is almost the same as your UCS.cpp. Only f(n), the number the queue sorts by, is different.

    // TODO 1: get the heuristic of the problem:
    //           std::shared_ptr<const core::HeuristicFunction> h = p.getHeuristicFunction();
    //         Then, like in UCS: the frontier with our rule CheaperFirst (in Greedy.h):
    //           std::priority_queue<core::NodePtr, std::vector<core::NodePtr>, CheaperFirst> frontier;
    //         core::StateSet explored;  and  int visitingOrder = 0;
    //         Question: the queue sorts the nodes by totalCost (Node::compareTo()).
    //                   For Greedy, what must totalCost be?

    // TODO 2: create the start node with FIVE values:
    //           std::make_shared<core::Node>(start, nullptr, nullptr, 0.0, h->getH(start))
    //         (start = p.getInitialState()). Add it to the frontier and count it: generatedNodes++
    //         Question: UCS used std::make_shared<core::Node>(start). Why is it not enough for Greedy?

    // TODO 3: while the frontier is not empty (!frontier.empty()):
    //   a) take the node with the smallest f(n), in two steps (like UCS):
    //        core::NodePtr currentNode = frontier.top();
    //        frontier.pop();
    //   b) graph search only: if explored.count(currentNode->getState()) > 0, skip it with "continue".
    //   c) currentNode->setVisitingOrder(++visitingOrder);
    //   d) goal test: if p.isGoal(currentNode->getState()), return currentNode.
    //   e) graph search only: explored.insert(currentNode->getState());
    //   f) expand the node: nodesActuallyExpanded++
    //      then for every action and every next state s (like in UCS):
    //        - double pathCost = currentNode->getPathCost() + p.getActionCost(currentNode->getState(), action, s);
    //          Question: Greedy does not use g(n) to choose. Why do we still compute it?
    //        - double f = h->getH(s);       <- the only line that makes it Greedy
    //        - core::NodePtr child = std::make_shared<core::Node>(s, currentNode, action, pathCost, f);
    //        - frontier.push(child);  and count it: generatedNodes++
    //   Question: run GreedyDemo. The path on the city map costs 21 km, but 18 km is possible. Why?

    // TODO 4: the queue is empty and we did not find a goal: return nullptr.
    return nullptr;
}

}  // namespace sa2026::algorithms::incomplete_code
