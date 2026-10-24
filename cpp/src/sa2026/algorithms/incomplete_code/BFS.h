#pragma once

#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/SearchAlgorithm.h"

namespace sa2026::algorithms::incomplete_code {

/*
 * STUDENT TASK: write the body of search() in BFS.cpp.
 * Everything else is ready. Search for "TODO" and follow the steps.
 * Check your work with BFSDemo.cpp (in this folder).
 *
 * Breadth-First Search (BFS), the standard version.
 *
 * BFS visits the nodes level by level: first depth 0, then depth 1, then depth 2 ...
 * The frontier is a queue (FIFO): the first node in is the first node out.
 *
 * Tree search:  we do not remember anything, so a state can come back many times.
 * Graph search: we remember the explored states and do not expand them again.
 *
 * BFS is optimal only when all the actions have the same cost.
 */
class BFS : public core::SearchAlgorithm {
public:
    // tree search
    BFS();

    // true = graph search, false = tree search
    explicit BFS(bool useGraphSearch);

    core::NodePtr search(const core::Problem& p) override;
};

}  // namespace sa2026::algorithms::incomplete_code
