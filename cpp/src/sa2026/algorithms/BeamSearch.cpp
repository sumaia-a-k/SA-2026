#include "sa2026/algorithms/BeamSearch.h"

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "sa2026/core/HeuristicFunction.h"

namespace sa2026::algorithms {

BeamSearch::BeamSearch(int beamWidth) : BeamSearch(beamWidth, false) {}

BeamSearch::BeamSearch(int beamWidth, bool useGraphSearch)
    : SearchAlgorithm(useGraphSearch), beamWidth(beamWidth) {
    if (beamWidth < 1) {
        throw std::invalid_argument("The beam width k must be 1 or more, not " + std::to_string(beamWidth) + ".");
    }
}

int BeamSearch::getBeamWidth() const {
    return beamWidth;
}

int BeamSearch::getThrownAwayNodes() const {
    return thrownAwayNodes;
}

core::NodePtr BeamSearch::search(const core::Problem& p) {
    resetCounters();
    thrownAwayNodes = 0;  // a new search: nothing thrown away yet

    // the guess h(n) of this problem (throws an error if the problem has no heuristic)
    std::shared_ptr<const core::HeuristicFunction> h = p.getHeuristicFunction();

    // the frontier is a vector, sorted by f(n): the best node is the first one (index 0)
    std::vector<core::NodePtr> frontier;
    core::StateSet explored;  // a hash set: count() is fast
    int visitingOrder = 0;

    // the start node: path cost 0, f(n) = h(n)
    core::StatePtr start = p.getInitialState();
    core::NodePtr startNode = std::make_shared<core::Node>(start, nullptr, nullptr, 0.0, h->getH(start));
    frontier.push_back(startNode);
    generatedNodes++;  // the start node is a generated node too

    while (!frontier.empty()) {
        // take the node with the smallest f(n): the first one in the vector
        core::NodePtr currentNode = frontier.front();
        frontier.erase(frontier.begin());

        // graph search: skip the other copies of a state we already expanded
        if (useGraphSearch && explored.count(currentNode->getState()) > 0) {
            continue;
        }

        currentNode->setVisitingOrder(++visitingOrder);

        // goal test when we take the node out of the frontier (like Greedy)
        if (p.isGoal(currentNode->getState())) {
            return currentNode;
        }

        if (useGraphSearch) {
            explored.insert(currentNode->getState());
        }

        // expand: apply every action and add the children to the end of the vector
        nodesActuallyExpanded++;
        for (const core::ActionPtr& action : p.getActions()) {
            std::vector<core::StatePtr> nextStates = action->apply(currentNode->getState());
            for (const core::StatePtr& s : nextStates) {
                // g(n): the real cost from the start (only to know the cost of the path)
                double pathCost = currentNode->getPathCost()
                                  + p.getActionCost(currentNode->getState(), action, s);
                // f(n) = h(n), like Greedy
                double f = h->getH(s);
                core::NodePtr child = std::make_shared<core::Node>(s, currentNode, action, pathCost, f);
                frontier.push_back(child);
                generatedNodes++;
            }
        }

        // sort the whole frontier by f(n) (our rule BetterFirst, in BeamSearch.h).
        // stable_sort keeps the order of two nodes with the same f(n), so the older one stays first.
        // (std::sort does not promise this.)
        std::stable_sort(frontier.begin(), frontier.end(), BetterFirst());

        // NEW in Beam Search: keep only the k best nodes, throw away the rest
        // (static_cast<int>: size() is not an int, and g++ warns when we compare them)
        while (static_cast<int>(frontier.size()) > beamWidth) {
            frontier.pop_back();  // the worst node is the last one
            thrownAwayNodes++;
        }
    }

    // the frontier is empty and we did not find a goal
    // (maybe there is a goal, but we threw its way away)
    return nullptr;
}

}  // namespace sa2026::algorithms
