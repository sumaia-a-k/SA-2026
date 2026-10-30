#pragma once

#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/SearchAlgorithm.h"

namespace sa2026::algorithms::incomplete_code {

/*
 * STUDENT TASK: write the body of search() in DFS.cpp.
 * Everything else is ready. Search for "TODO" and follow the steps.
 * Check your work with DFSDemo.cpp (in this folder).
 *
 * Depth-First Search (DFS), the standard version.
 *
 * DFS always goes deeper first. At a dead end it goes back
 * to the newest node that is still waiting in the stack.
 * The frontier is a stack (LIFO): the last node in is the first node out.
 *
 * Tree search:  we do not remember anything. In a graph with cycles
 *               DFS can go around a cycle forever!
 * Graph search: we remember the explored states and do not expand them again.
 *
 * DFS is not optimal: the first path it finds can be a long one.
 */
class DFS : public core::SearchAlgorithm {
public:
    // tree search
    DFS();

    // true = graph search, false = tree search
    explicit DFS(bool useGraphSearch);

    core::NodePtr search(const core::Problem& p) override;
};

}  // namespace sa2026::algorithms::incomplete_code
