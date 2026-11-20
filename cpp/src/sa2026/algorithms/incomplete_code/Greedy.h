#pragma once

#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/SearchAlgorithm.h"

namespace sa2026::algorithms::incomplete_code {

/*
 * STUDENT TASK: write the body of search() in Greedy.cpp.
 * Everything else is ready. Search for "TODO" and follow the steps.
 * Check your work with GreedyDemo.cpp (in this folder).
 *
 * Greedy Best-First Search.
 *
 * Greedy always expands the node that LOOKS closest to the goal:
 * the node with the smallest guess h(n). So f(n) = h(n).
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
