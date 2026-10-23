#pragma once

#include "sa2026/core/Node.h"
#include "sa2026/core/Problem.h"

namespace sa2026::core {

/*
 * The parent class of all search algorithms (BFS, DFS, UCS, A*, ...).
 * Each algorithm writes its own search() method.
 */
class SearchAlgorithm {
public:
    virtual ~SearchAlgorithm() = default;

    /*
     * Searches for a goal and returns the goal node, or nullptr if there is no solution.
     * Call resetCounters() at the start, so the numbers are correct
     * when the same algorithm object is used more than once.
     */
    virtual NodePtr search(const Problem& p) = 0;

    bool isGraphSearch() const;
    int getGeneratedNodes() const;
    int getNodesActuallyExpanded() const;

    // prints every step from the start to the goal
    void printSolution(const NodePtr& solution) const;

protected:
    // tree search by default
    SearchAlgorithm();

    // the child algorithm passes its mode here, for example: BFS(bool g) : SearchAlgorithm(g) {}
    explicit SearchAlgorithm(bool useGraphSearch);

    // sets the counters back to 0
    void resetCounters();

    // false = tree search (a state can be visited again)
    // true  = graph search (we remember explored states and do not visit them again)
    const bool useGraphSearch;

    // number of nodes created (generated): the start node + every child node
    int generatedNodes = 0;

    // number of nodes taken from the frontier and expanded
    int nodesActuallyExpanded = 0;
};

}  // namespace sa2026::core
