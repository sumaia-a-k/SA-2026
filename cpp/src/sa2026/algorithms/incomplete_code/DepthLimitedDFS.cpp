#include "sa2026/algorithms/incomplete_code/DepthLimitedDFS.h"

#include <memory>  // you need them in the TODOs
#include <stack>
#include <vector>

namespace sa2026::algorithms::incomplete_code {

DepthLimitedDFS::DepthLimitedDFS(int limit) : SearchAlgorithm(false), limit(limit) {}

bool DepthLimitedDFS::isCutoff() const {
    return cutoff;
}

core::NodePtr DepthLimitedDFS::search(const core::Problem& p) {
    resetCounters();

    // TODO 1: a new search: no cutoff yet, so set cutoff = false.
    //         Question: what goes wrong if the same object is used two times and we forget this?

    // TODO 2: create the frontier (a std::stack<core::NodePtr>) and visitingOrder = 0.
    //         Create the start node, push it and count it (generatedNodes++).

    // TODO 3: while the frontier is not empty:
    //   a) take the top node (top() and then pop()), and set its visiting order.
    //   b) goal test: if p.isGoal(currentNode->getState()), return currentNode.
    //   c) THE CHANGE: if currentNode->getDepth() >= limit:
    //        set cutoff = true, and do not expand the node ("continue").
    //      Question: why is the goal test BEFORE this test, and not after it?
    //   d) expand the node: nodesActuallyExpanded++
    //      then for every action and every next state s (like in DFSCycleCheck):
    //        - if isOnPath(currentNode, s), skip s ("continue")
    //        - create the child node with its pathCost, push it and count it (generatedNodes++).

    // TODO 4: the stack is empty and we did not find a goal: return nullptr.
    return nullptr;
}

bool DepthLimitedDFS::isOnPath(const core::NodePtr& node, const core::StatePtr& s) {
    // TODO 5: the same as isOnPath() in your DFSCycleCheck.cpp
    return false;
}

}  // namespace sa2026::algorithms::incomplete_code
