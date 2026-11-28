#include "sa2026/algorithms/incomplete_code/BeamSearch.h"

#include <algorithm>  // you need them in the TODOs
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "sa2026/core/HeuristicFunction.h"

namespace sa2026::algorithms::incomplete_code {

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

    // The code is almost the same as your Greedy.cpp. Only the frontier and one new step are different.

    // TODO 1: like in Greedy:
    //           std::shared_ptr<const core::HeuristicFunction> h = p.getHeuristicFunction();
    //         core::StateSet explored;  and  int visitingOrder = 0;
    //         NEW: the frontier is a vector, not a priority_queue:
    //           std::vector<core::NodePtr> frontier;
    //         Question: why can we not use a priority_queue here? (Look at TODO 3 h.)

    // TODO 2: like in Greedy: create the start node with FIVE values:
    //           std::make_shared<core::Node>(start, nullptr, nullptr, 0.0, h->getH(start))
    //         (start = p.getInitialState()). Add it with frontier.push_back(...) and count it: generatedNodes++

    // TODO 3: while the frontier is not empty (!frontier.empty()):
    //   a) take the best node. The vector is sorted, so the best node is the first one (two steps):
    //        core::NodePtr currentNode = frontier.front();
    //        frontier.erase(frontier.begin());
    //   b) graph search only: if explored.count(currentNode->getState()) > 0, skip it with "continue".
    //   c) currentNode->setVisitingOrder(++visitingOrder);
    //   d) goal test: if p.isGoal(currentNode->getState()), return currentNode.
    //   e) graph search only: explored.insert(currentNode->getState());
    //   f) expand the node, like in Greedy: nodesActuallyExpanded++
    //      then for every action and every next state s:
    //        - double pathCost = currentNode->getPathCost() + p.getActionCost(currentNode->getState(), action, s);
    //        - double f = h->getH(s);
    //        - core::NodePtr child = std::make_shared<core::Node>(s, currentNode, action, pathCost, f);
    //        - frontier.push_back(child);  (at the end for now)  and count it: generatedNodes++
    //   g) after the for loops: sort the WHOLE frontier by f(n), with our rule BetterFirst (in BeamSearch.h):
    //        std::stable_sort(frontier.begin(), frontier.end(), BetterFirst());
    //      Question: two nodes have the same h. Which one is first after the sort?
    //                (stable_sort does not change the order of equal nodes. std::sort does not promise it.)
    //   h) NEW in Beam Search: keep only the k best nodes. While static_cast<int>(frontier.size()) > beamWidth:
    //        - remove the last node (the worst one):  frontier.pop_back();
    //        - count it: thrownAwayNodes++
    //      Question: can a node that was in the frontier BEFORE this step be thrown away too?
    //                (Look at step 3 of the trace on beam.html.)
    //   Question: run BeamDemo. With the misleading guess and k = 1 your search returns nullptr,
    //             but the path S -> B -> E -> G exists. Why?

    // TODO 4: the frontier is empty and we did not find a goal: return nullptr.
    return nullptr;
}

}  // namespace sa2026::algorithms::incomplete_code
