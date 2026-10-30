#pragma once

#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/SearchAlgorithm.h"
#include "sa2026/core/State.h"

namespace sa2026::algorithms::incomplete_code {

/*
 * STUDENT TASK: write the body of search() and the body of isOnPath() in DFSCycleCheck.cpp.
 * Do DFS.cpp first: this class is DFS tree search with one small change.
 * Search for "TODO" and follow the steps. Check your work with DFSDemo.cpp (in this folder).
 *
 * DFS tree search with a cycle check (also called "path check").
 *
 * A cycle is ONE path that comes back to a state that is already on it,
 * for example S -> A -> S. Tree search DFS can go around a cycle forever.
 *
 * Graph search stops cycles with an explored set, but that set keeps EVERY state
 * we expanded (a lot of memory). Here we only look at the path of the node:
 * node -> parent -> parent ... -> start. We do not push a child whose state is on it.
 *
 * Good:  every cycle is stopped, and we need no new memory (the parents are already there).
 * Bad:   the same state can still come again on a DIFFERENT path, so we can do more work.
 */
class DFSCycleCheck : public core::SearchAlgorithm {
public:
    DFSCycleCheck();  // tree search with a cycle check

    core::NodePtr search(const core::Problem& p) override;

private:
    // true if the state is in this node or in one of its parents
    static bool isOnPath(const core::NodePtr& node, const core::StatePtr& s);
};

}  // namespace sa2026::algorithms::incomplete_code
