#pragma once

#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/SearchAlgorithm.h"

namespace sa2026::algorithms {

/*
 * Uniform-Cost Search (UCS).
 *
 * UCS always expands the CHEAPEST node first: the node with the smallest
 * path cost g(n) (the real cost from the start to the node).
 * The frontier is a priority queue: top() always gives the node with the smallest cost.
 *
 * The code is the same as BFS. Only the frontier is different:
 *   BFS: a queue           -> takes the OLDEST node    (fewest steps)
 *   UCS: a priority queue  -> takes the CHEAPEST node  (smallest cost)
 *
 * Tree search:  we do not remember anything, so a state can come back many times.
 * Graph search: we remember the explored states and do not expand them again.
 *
 * UCS is optimal when every action costs more than 0.
 * If all the actions cost the same, UCS expands the nodes like BFS.
 */
class UCS : public core::SearchAlgorithm {
public:
    // tree search
    UCS();

    // true = graph search, false = tree search
    explicit UCS(bool useGraphSearch);

    core::NodePtr search(const core::Problem& p) override;

private:
    /*
     * The rule of our priority queue. std::priority_queue puts the BIGGEST item on the top,
     * so we turn the rule around: "a is bigger than b" when a costs MORE (compareTo() > 0).
     * Then the CHEAPEST node is on the top.
     */
    struct CheaperFirst {
        bool operator()(const core::NodePtr& a, const core::NodePtr& b) const {
            return a->compareTo(*b) > 0;
        }
    };
};

}  // namespace sa2026::algorithms
