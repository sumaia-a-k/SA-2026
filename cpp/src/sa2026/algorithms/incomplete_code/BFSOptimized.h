#pragma once

#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/SearchAlgorithm.h"

namespace sa2026::algorithms::incomplete_code {

/*
 * STUDENT TASK: write the body of search() in BFSOptimized.cpp.
 * Do BFS first: this class is the same, with one small change.
 * Search for "TODO" and follow the steps. Check your work with BFSDemo.cpp (in this folder).
 *
 * BFS with one small change for graph search:
 * we check the state when we CREATE the child, not when we take it out of the queue.
 *
 * In the standard BFS the same state can go into the queue many times
 * (it is skipped later, but it still uses memory).
 * Here "reached" has every state we generated: the states in the queue
 * and the states already expanded. So each state goes into the queue only once.
 *
 * Why "reached" and not "visited"? People use "visited" for two different things
 * (added to the queue, or expanded). "reached" is the name in the AIMA book.
 *
 * The answer is the same as the standard BFS. We only use less memory and less time.
 * In tree search mode this class works exactly like the standard BFS.
 */
class BFSOptimized : public core::SearchAlgorithm {
public:
    // tree search
    BFSOptimized();

    // true = graph search, false = tree search
    explicit BFSOptimized(bool useGraphSearch);

    core::NodePtr search(const core::Problem& p) override;
};

}  // namespace sa2026::algorithms::incomplete_code
