#pragma once

#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/SearchAlgorithm.h"
#include "sa2026/core/State.h"

namespace sa2026::algorithms {

/*
 * Hill Climbing (steepest): a local search.
 *
 * It keeps only ONE state: the current one. No frontier, no explored set.
 * At every step it looks at ALL the neighbours, takes the best one (the smallest h),
 * and moves there ONLY IF it is better: h(best) < h(current).
 * If no neighbour is better, it stops. Same h: the first neighbour wins.
 *
 * We minimize h (a distance to the goal, smaller is better).
 *
 * search() returns the goal node, or nullptr when it is stuck (it stopped, but not at a goal).
 * Then getStuckNode() gives the state where it stopped: the best state of this climb.
 *
 * NOT complete (it can get stuck: local minimum, plateau, ridge). NOT optimal.
 * It is NOT tree search and NOT graph search: it has no frontier and no explored set.
 * It needs no explored set: h gets smaller at every move, so it can never come back to an old state.
 */
class HillClimbing : public core::SearchAlgorithm {
public:
    // no useGraphSearch here: Hill Climbing is not tree search and not graph search
    HillClimbing();

    // the node where the last search stopped without a goal (nullptr after a success)
    core::NodePtr getStuckNode() const;

    core::NodePtr search(const core::Problem& p) override;

    /*
     * One climb from the state "start". RandomRestart calls it with random start states.
     * It does not reset the counters, so RandomRestart can count all its climbs together.
     */
    core::NodePtr climb(const core::Problem& p, const core::StatePtr& start);

private:
    core::NodePtr stuckNode;  // where the last climb stopped, when it did not find a goal
};

}  // namespace sa2026::algorithms
