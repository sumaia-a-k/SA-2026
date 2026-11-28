#pragma once

#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/SearchAlgorithm.h"
#include "sa2026/core/State.h"

namespace sa2026::algorithms::incomplete_code {

/*
 * STUDENT TASK: write the body of climb() in HillClimbing.cpp.
 * Everything else is ready. Search for "TODO" and follow the steps.
 * Check your work with HillClimbingDemo.cpp (in this folder).
 *
 * Hill Climbing (steepest): a local search.
 *
 * It keeps only ONE state: the current one. No frontier, no explored set.
 * At every step it looks at ALL the neighbours, takes the best one (the smallest h),
 * and moves there ONLY IF it is better: h(best) < h(current).
 * If no neighbour is better, it stops. Same h: the first neighbour wins.
 *
 * search() returns the goal node, or nullptr when it is stuck.
 * Then getStuckNode() gives the state where it stopped.
 */
class HillClimbing : public core::SearchAlgorithm {
public:
    // no useGraphSearch here: Hill Climbing is not tree search and not graph search
    HillClimbing();

    // the node where the last search stopped without a goal (nullptr after a success)
    core::NodePtr getStuckNode() const;

    core::NodePtr search(const core::Problem& p) override;

    // one climb from the state "start"
    core::NodePtr climb(const core::Problem& p, const core::StatePtr& start);

private:
    core::NodePtr stuckNode;  // where the last climb stopped, when it did not find a goal
};

}  // namespace sa2026::algorithms::incomplete_code
