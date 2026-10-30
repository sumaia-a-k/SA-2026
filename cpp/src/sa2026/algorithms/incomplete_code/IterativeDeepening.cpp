#include "sa2026/algorithms/incomplete_code/IterativeDeepening.h"

#include "sa2026/algorithms/incomplete_code/DepthLimitedDFS.h"  // your DLS

namespace sa2026::algorithms::incomplete_code {

IterativeDeepening::IterativeDeepening() : SearchAlgorithm(false) {}

core::NodePtr IterativeDeepening::search(const core::Problem& p) {
    resetCounters();

    // TODO 1: a loop that never stops by itself:  for (int limit = 0;; limit++) {
    //   a) create a DepthLimitedDFS with this limit (your class, in this folder),
    //      and run it:  DepthLimitedDFS dls(limit);  core::NodePtr result = dls.search(p);
    //   b) add its counters to ours, so we count the work of EVERY iteration:
    //        generatedNodes += dls.getGeneratedNodes();
    //        nodesActuallyExpanded += dls.getNodesActuallyExpanded();
    //   c) if result is not nullptr, we found the goal: return result.
    //   d) if dls.isCutoff() is false, no node stopped at the limit.
    //      We searched everything, so there is no solution: return nullptr.
    //      Question: what happens if we forget this test and there is no solution?
    // }
    return nullptr;
}

}  // namespace sa2026::algorithms::incomplete_code
