#pragma once

#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/SearchAlgorithm.h"

namespace sa2026::algorithms {

/*
 * A* Search.
 *
 * A* always expands the node with the smallest f(n) = g(n) + h(n):
 *   g(n) = the real cost from the start to n (we already paid it)
 *   h(n) = a guess of the cost from n to the goal
 * So f(n) is a guess of the cost of the WHOLE path through n.
 *
 * The code is the same as UCS. Only f(n), the number the queue sorts by, is different:
 *   UCS: f(n) = g(n)    (it is A* with h(n) = 0)
 *   A*:  f(n) = g(n) + h(n)
 *
 * A* is complete (like UCS, when every cost is more than 0).
 * A* is optimal:
 *   tree search  -> if h is admissible  (h(n) <= the real cost to the goal)
 *   graph search -> if h is consistent  (h(n) <= c(n, n') + h(n') for every child n')
 * Our graph search never puts an explored state back in the queue,
 * so it needs the stronger rule: consistent.
 */
class AStar : public core::SearchAlgorithm {
public:
    // tree search
    AStar();

    // true = graph search, false = tree search
    explicit AStar(bool useGraphSearch);

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
