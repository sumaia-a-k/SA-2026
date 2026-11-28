#pragma once

#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/SearchAlgorithm.h"

namespace sa2026::algorithms {

/*
 * Beam Search.
 *
 * Beam Search is Greedy with a small frontier. The frontier can keep only
 * k nodes (k = the beam width). After each expansion we sort the WHOLE frontier
 * (old nodes and new children together) by f(n) = h(n), keep the k best nodes
 * and throw away the rest. A node that we throw away never comes back.
 *
 * The code is the same as Greedy. Only two things are different:
 *   1. the frontier is a vector, not a priority_queue, because we must cut it
 *   2. one new step after each expansion: keep only the k best nodes
 * Same h: the node that came into the frontier first stays first (std::stable_sort keeps the order).
 *
 * k = 1:         only one node in the frontier. It always goes to the best child (close to Hill Climbing).
 * k = no limit:  nothing is thrown away. It is Greedy (only nodes with the same h
 *                can come out in another order: a priority_queue does not keep the order).
 *
 * Tree search and graph search: NOT complete. The way to the goal can be thrown away.
 * Beam Search is NOT optimal. Its good point: the frontier has at most k nodes after each step.
 */
class BeamSearch : public core::SearchAlgorithm {
public:
    // tree search
    explicit BeamSearch(int beamWidth);

    // true = graph search, false = tree search
    BeamSearch(int beamWidth, bool useGraphSearch);

    int getBeamWidth() const;
    int getThrownAwayNodes() const;

    core::NodePtr search(const core::Problem& p) override;

private:
    // the rule of our sort: the node with the smaller totalCost, here f(n), comes first.
    // (Greedy.h has the opposite rule, because a priority_queue puts the "biggest" node on the top.)
    struct BetterFirst {
        bool operator()(const core::NodePtr& a, const core::NodePtr& b) const {
            return a->compareTo(*b) < 0;
        }
    };

    const int beamWidth;      // k: the most nodes the frontier can keep
    int thrownAwayNodes = 0;  // how many nodes the last search threw away
};

}  // namespace sa2026::algorithms
