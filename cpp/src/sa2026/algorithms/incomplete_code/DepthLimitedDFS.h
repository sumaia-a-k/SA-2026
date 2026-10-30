#pragma once

#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/SearchAlgorithm.h"
#include "sa2026/core/State.h"

namespace sa2026::algorithms::incomplete_code {

/*
 * STUDENT TASK: write the body of search() and the body of isOnPath() in DepthLimitedDFS.cpp.
 * Do DFSCycleCheck.cpp first: this class is the same, with a depth limit.
 * Search for "TODO" and follow the steps. Check your work with DFSDemo.cpp (in this folder).
 *
 * Depth-Limited Search (DLS): DFS with a cycle check and a depth limit.
 *
 * A node at depth = limit is NOT expanded. So DFS can not go down forever.
 *
 * limit < depth of the goal:  no goal is found (returns nullptr).
 * limit = depth of the goal:  a shortest path is found (if all steps cost the same).
 * limit > depth of the goal:  a goal is found, but maybe a long path.
 *
 * When it returns nullptr, isCutoff() tells us why:
 *   true  = a node stopped at the limit: maybe there is a goal deeper.
 *   false = we searched everything: there is no goal at all.
 */
class DepthLimitedDFS : public core::SearchAlgorithm {
public:
    explicit DepthLimitedDFS(int limit);  // tree search with a cycle check

    // IDS asks this after the search: true = try a bigger limit, false = no solution
    bool isCutoff() const;

    core::NodePtr search(const core::Problem& p) override;

private:
    // true if the state is in this node or in one of its parents
    static bool isOnPath(const core::NodePtr& node, const core::StatePtr& s);

    const int limit;      // do not expand nodes at this depth
    bool cutoff = false;  // only a flag: did at least one node stop at the limit? (yes / no)
};

}  // namespace sa2026::algorithms::incomplete_code
