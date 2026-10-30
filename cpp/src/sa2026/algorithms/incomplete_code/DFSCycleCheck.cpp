#include "sa2026/algorithms/incomplete_code/DFSCycleCheck.h"

#include <memory>  // you need them in the TODOs
#include <stack>
#include <vector>

namespace sa2026::algorithms::incomplete_code {

DFSCycleCheck::DFSCycleCheck() : SearchAlgorithm(false) {}

core::NodePtr DFSCycleCheck::search(const core::Problem& p) {
    resetCounters();

    // TODO 1: create the frontier (a std::stack<core::NodePtr>) and visitingOrder = 0.
    //         There is NO explored set here. Question: why not?

    // TODO 2: create the start node, push it and count it (generatedNodes++).

    // TODO 3: while the frontier is not empty:
    //   a) take the top node (top() and then pop()), and set its visiting order.
    //   b) goal test: if p.isGoal(currentNode->getState()), return currentNode.
    //   c) expand the node: nodesActuallyExpanded++
    //      then for every action and every next state s (like in DFS):
    //        - THE CHANGE: if isOnPath(currentNode, s) is true, skip s ("continue").
    //          It would make a cycle.
    //        - create the child node with its pathCost, push it and count it (generatedNodes++).

    // TODO 4: the stack is empty and we did not find a goal: return nullptr.
    return nullptr;
}

bool DFSCycleCheck::isOnPath(const core::NodePtr& node, const core::StatePtr& s) {
    // TODO 5: go from the node up to the start, one parent at a time:
    //           for (core::NodePtr n = node; n != nullptr; n = n->getParent())
    //         If n->getState()->equals(*s), return true.
    //         At the end (we reached above the start node): return false.
    //         Question: why do we need equals() here, and not == ?
    return false;
}

}  // namespace sa2026::algorithms::incomplete_code
