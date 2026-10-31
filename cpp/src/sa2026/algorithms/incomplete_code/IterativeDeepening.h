#pragma once

#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/SearchAlgorithm.h"

namespace sa2026::algorithms::incomplete_code {

/*
 * STUDENT TASK: write the body of search() in IterativeDeepening.cpp.
 * Do DepthLimitedDFS.cpp first: IDS only calls it again and again.
 * Search for "TODO" and follow the steps. Check your work with DFSDemo.cpp (in this folder).
 *
 * Iterative Deepening Search (IDS).
 *
 * We do not know the depth of the goal, so we try every limit:
 * DepthLimitedDFS with limit 0, then 1, then 2, ... until we find the goal.
 *
 * The first limit that finds a goal is its depth, so the path is a shortest one
 * (the same answer as BFS, if all steps cost the same).
 * But the memory is small, like DFS: only one path and the nodes that wait next to it.
 */
class IterativeDeepening : public core::SearchAlgorithm {
public:
    IterativeDeepening();  // every iteration is a tree search with a cycle check

    core::NodePtr search(const core::Problem& p) override;
};

}  // namespace sa2026::algorithms::incomplete_code
