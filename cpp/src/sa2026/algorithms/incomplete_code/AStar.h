#pragma once

#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/SearchAlgorithm.h"

namespace sa2026::algorithms::incomplete_code {

/*
 * STUDENT TASK: write the body of search() in AStar.cpp.
 * Everything else is ready. Search for "TODO" and follow the steps.
 * Check your work with AStarDemo.cpp (in this folder).
 *
 * A* Search.
 *
 * A* always expands the node with the smallest f(n) = g(n) + h(n):
 *   g(n) = the real cost from the start to n (we already paid it)
 *   h(n) = a guess of the cost from n to the goal
 *
 * A* is complete (like UCS, when every cost is more than 0).
 * A* is optimal:
 *   tree search  -> if h is admissible
 *   graph search -> if h is consistent
 */
class AStar : public core::SearchAlgorithm {
public:
    // tree search
    AStar();

    // true = graph search, false = tree search
    explicit AStar(bool useGraphSearch);

    core::NodePtr search(const core::Problem& p) override;

private:
    /*
     * The rule of our priority queue (ready for you, use it in TODO 1).
     * It is the same rule as in UCS.h: the node with the smallest totalCost is on the top.
     * Here totalCost = f(n).
     */
    struct CheaperFirst {
        bool operator()(const core::NodePtr& a, const core::NodePtr& b) const {
            return a->compareTo(*b) > 0;
        }
    };
};

}  // namespace sa2026::algorithms::incomplete_code
