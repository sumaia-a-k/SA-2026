#include "sa2026/algorithms/incomplete_code/DFS.h"

#include <memory>  // you need them in the TODOs
#include <stack>
#include <vector>

namespace sa2026::algorithms::incomplete_code {

DFS::DFS() : SearchAlgorithm(false) {}

DFS::DFS(bool useGraphSearch) : SearchAlgorithm(useGraphSearch) {}

core::NodePtr DFS::search(const core::Problem& p) {
    resetCounters();

    // The code is almost the same as your BFS.cpp. Only the frontier is different.

    // TODO 1: create the frontier, a stack of nodes:  std::stack<core::NodePtr> frontier;
    //         create the set of explored states:     core::StateSet explored;
    //         and a counter:                         int visitingOrder = 0;

    // TODO 2: create the start node:  std::make_shared<core::Node>(p.getInitialState())
    //         and PUSH it on the stack (frontier.push(...)). Count it: generatedNodes++

    // TODO 3: while the frontier is not empty (!frontier.empty()):
    //   a) take the newest node from the top of the stack. In C++ this needs two steps:
    //        core::NodePtr currentNode = frontier.top();   // read the top node
    //        frontier.pop();                                // remove it
    //      Question: this is the only part that makes it DFS and not BFS. Why?
    //   b) graph search only: if explored.count(currentNode->getState()) > 0, skip it ("continue").
    //   c) currentNode->setVisitingOrder(++visitingOrder);
    //   d) goal test: if p.isGoal(currentNode->getState()), return currentNode.
    //   e) graph search only: explored.insert(currentNode->getState());
    //   f) expand the node: nodesActuallyExpanded++
    //      then for every action and every next state s (like in BFS):
    //        - create the child node with its pathCost (like in BFS)
    //        - PUSH the child on the top of the stack (frontier.push(child)),
    //          and count it: generatedNodes++
    //      Question: the children are pushed in the order of the actions.
    //                Which child does DFS take first?

    // TODO 4: the stack is empty and we did not find a goal: return nullptr.
    return nullptr;
}

}  // namespace sa2026::algorithms::incomplete_code
