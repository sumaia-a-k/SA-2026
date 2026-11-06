#include "sa2026/algorithms/IterativeDeepening.h"

#include "sa2026/algorithms/DepthLimitedDFS.h"

namespace sa2026::algorithms {

IterativeDeepening::IterativeDeepening() : SearchAlgorithm(false) {}

core::NodePtr IterativeDeepening::search(const core::Problem& p) {
    resetCounters();

    // try limit 0, 1, 2, ... until we find the goal
    for (int limit = 0;; limit++) {
        DepthLimitedDFS dls(limit);
        core::NodePtr result = dls.search(p);

        // count the work of every iteration
        generatedNodes += dls.getGeneratedNodes();
        nodesActuallyExpanded += dls.getNodesActuallyExpanded();

        if (result != nullptr) {
            return result;   // found the goal
        }
        if (!dls.isCutoff()) {
            return nullptr;  // no node stopped at the limit: there is no solution
        }
    }
}

}  // namespace sa2026::algorithms
