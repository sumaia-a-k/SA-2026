#pragma once

#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/SearchAlgorithm.h"

namespace sa2026::algorithms::incomplete_code {

/*
 * STUDENT TASK: write the body of search() in BeamSearch.cpp.
 * Everything else is ready. Search for "TODO" and follow the steps.
 * Check your work with BeamDemo.cpp (in this folder).
 *
 * Beam Search.
 *
 * Beam Search is Greedy with a small frontier. The frontier can keep only
 * k nodes (k = the beam width). After each expansion we sort the WHOLE frontier
 * (old nodes and new children together) by f(n) = h(n), keep the k best nodes
 * and throw away the rest. A node that we throw away never comes back.
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
    /*
     * The rule of our sort (ready for you, use it in TODO 3 g).
     * The node with the smaller totalCost, here f(n), comes first.
     * (Greedy.h has the opposite rule, because a priority_queue puts the "biggest" node on the top.)
     */
    struct BetterFirst {
        bool operator()(const core::NodePtr& a, const core::NodePtr& b) const {
            return a->compareTo(*b) < 0;
        }
    };

    const int beamWidth;      // k: the most nodes the frontier can keep
    int thrownAwayNodes = 0;  // how many nodes the last search threw away
};

}  // namespace sa2026::algorithms::incomplete_code
