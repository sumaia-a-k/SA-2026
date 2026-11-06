#include "sa2026/algorithms/incomplete_code/UCS.h"

#include <memory>  // you need them in the TODOs
#include <queue>
#include <vector>

namespace sa2026::algorithms::incomplete_code {

UCS::UCS() : SearchAlgorithm(false) {}

UCS::UCS(bool useGraphSearch) : SearchAlgorithm(useGraphSearch) {}

core::NodePtr UCS::search(const core::Problem& p) {
    resetCounters();

    // The code is almost the same as your BFS.cpp. Only the frontier is different.

    // TODO 1: create the frontier, a PRIORITY queue of nodes, with our rule CheaperFirst (in UCS.h):
    //           std::priority_queue<core::NodePtr, std::vector<core::NodePtr>, CheaperFirst> frontier;
    //         create the set of explored states:  core::StateSet explored;
    //         and a counter:                      int visitingOrder = 0;
    //         Question: how does the priority queue know which node is the cheapest?
    //                   (Look at CheaperFirst, Node::compareTo() and the Node constructors.)

    // TODO 2: create the start node:  std::make_shared<core::Node>(p.getInitialState())
    //         and add it to the frontier (frontier.push(...)). Count it: generatedNodes++
    //         Question: what is the path cost of the start node?

    // TODO 3: while the frontier is not empty (!frontier.empty()):
    //   a) take the CHEAPEST node out of the queue. In C++ this needs two steps:
    //        core::NodePtr currentNode = frontier.top();   // read the cheapest node (BFS: front())
    //        frontier.pop();                                // remove it
    //      Question: this is the only part that makes it UCS and not BFS. Why?
    //   b) graph search only: if explored.count(currentNode->getState()) > 0, skip it with "continue".
    //      Question: the same state can be in the queue two times, with two different costs.
    //                Which copy comes out first?
    //   c) currentNode->setVisitingOrder(++visitingOrder);
    //   d) goal test: if p.isGoal(currentNode->getState()), return currentNode.
    //      Question: in BFS it was only "better" to test the goal here.
    //                In UCS it is a MUST. Why? (Hint: S -> G costs 10, S -> A -> G costs 2.)
    //   e) graph search only: explored.insert(currentNode->getState());
    //   f) expand the node: nodesActuallyExpanded++
    //      then for every action and every next state s (like in BFS):
    //        - double pathCost = currentNode->getPathCost() + p.getActionCost(currentNode->getState(), action, s);
    //          Be careful: add the cost of THIS action to the cost of the parent.
    //        - core::NodePtr child = std::make_shared<core::Node>(s, currentNode, action, pathCost);
    //        - add the child to the queue (frontier.push(child)), and count it: generatedNodes++
    //          The queue puts it in the right place for you (sorted by cost).

    // TODO 4: the queue is empty and we did not find a goal: return nullptr.
    return nullptr;
}

}  // namespace sa2026::algorithms::incomplete_code
