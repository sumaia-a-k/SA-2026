#pragma once

#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/SearchAlgorithm.h"

namespace sa2026::algorithms {

/*
 * Greedy Best-First Search.
 *
 * Greedy always expands the node that LOOKS closest to the goal:
 * the node with the smallest guess h(n). So f(n) = h(n).
 *
 * The code is the same as UCS. Only f(n), the number the queue sorts by, is different:
 *   UCS:    f(n) = g(n)   the real cost so far
 *   Greedy: f(n) = h(n)   the guess to the goal
 * We still compute g(n) (pathCost), but only to know the cost of the path at the end.
 *
 * Tree search:  can go around a loop forever, even with a good heuristic.
 * Graph search: complete (when the number of states is finite).
 *
 * Greedy is NOT optimal, with any heuristic. It is often fast.
 */
class Greedy : public core::SearchAlgorithm {
public:
    // tree search
    Greedy();

    // true = graph search, false = tree search
    explicit Greedy(bool useGraphSearch);

    core::NodePtr search(const core::Problem& p) override;

private:
    // the same rule as in UCS.h: the node with the smallest totalCost, here f(n), is on the top
    struct CheaperFirst {
        bool operator()(const core::NodePtr& a, const core::NodePtr& b) const {
            return a->compareTo(*b) > 0;
        }
    };
};

}  // namespace sa2026::algorithms
