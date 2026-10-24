#include "sa2026/algorithms/incomplete_code/BFSOptimized.h"

#include <memory>  // you need them in the TODOs
#include <queue>
#include <vector>

namespace sa2026::algorithms::incomplete_code {

BFSOptimized::BFSOptimized() : SearchAlgorithm(false) {}

BFSOptimized::BFSOptimized(bool useGraphSearch) : SearchAlgorithm(useGraphSearch) {}

core::NodePtr BFSOptimized::search(const core::Problem& p) {
    resetCounters();

    // TODO 1: create the frontier (a std::queue<core::NodePtr>), the set "reached" (a core::StateSet)
    //         and the counter visitingOrder = 0.
    //         "reached" = every state we generated: the states in the queue AND the expanded ones.

    // TODO 2: create the start node, add it to the frontier and count it (generatedNodes++).
    //         Graph search only: add its state to "reached" too.
    //         Question: what goes wrong if we forget to add the start state here?

    // TODO 3: while the frontier is not empty:
    //   a) take the oldest node out of the queue (front(), then pop()).
    //      There is NO "explored" check here. Question: why do we not need it?
    //   b) currentNode->setVisitingOrder(++visitingOrder);
    //   c) goal test: if p.isGoal(currentNode->getState()), return currentNode.
    //   d) expand the node: nodesActuallyExpanded++
    //      then for every action and every next state s (like in BFS):
    //        - THE CHANGE: graph search only:
    //            if reached.count(s) > 0, skip it ("continue"),
    //            else reached.insert(s)
    //        - create the child node with its pathCost (like in BFS),
    //          add it to the end of the queue and count it (generatedNodes++)

    // TODO 4: the queue is empty and we did not find a goal: return nullptr.
    return nullptr;
}

}  // namespace sa2026::algorithms::incomplete_code
