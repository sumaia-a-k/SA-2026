#include "sa2026/algorithms/incomplete_code/HillClimbing.h"

#include <memory>
#include <vector>

#include "sa2026/core/HeuristicFunction.h"

namespace sa2026::algorithms::incomplete_code {

HillClimbing::HillClimbing() {}

core::NodePtr HillClimbing::getStuckNode() const {
    return stuckNode;
}

core::NodePtr HillClimbing::search(const core::Problem& p) {
    resetCounters();
    return climb(p, p.getInitialState());
}

core::NodePtr HillClimbing::climb(const core::Problem& p, const core::StatePtr& start) {
    stuckNode = nullptr;

    // TODO 1: get the heuristic:
    //           std::shared_ptr<const core::HeuristicFunction> h = p.getHeuristicFunction();
    //         and int visitingOrder = 0.
    //         Question: Hill Climbing has no frontier and no explored set. What does it keep?

    // TODO 2: create the current node with FIVE values (like in Greedy):
    //           core::NodePtr current = std::make_shared<core::Node>(start, nullptr, nullptr, 0.0, h->getH(start));
    //         and count it: generatedNodes++

    // TODO 3: while (true):
    //   a) current->setVisitingOrder(++visitingOrder);
    //   b) goal test: if p.isGoal(current->getState()), return current.
    //   c) look at ALL the neighbours: nodesActuallyExpanded++
    //      core::NodePtr best = nullptr;
    //      for every action and every next state s (like in Greedy):
    //        - pathCost = current->getPathCost() + p.getActionCost(current->getState(), action, s)
    //        - core::NodePtr child = std::make_shared<core::Node>(s, current, action, pathCost, h->getH(s));
    //        - count it: generatedNodes++
    //        - keep the best one: if best == nullptr or child->getTotalCost() < best->getTotalCost(), best = child
    //          Question: why "<" and not "<="? Which neighbour wins when two have the same h?
    //   d) stop if no neighbour is better:
    //        if best == nullptr or best->getTotalCost() >= current->getTotalCost():
    //            stuckNode = current;  return nullptr;
    //      Question: why ">=" and not ">"? What happens on a flat place if we use ">"?
    //   e) move: current = best;
    //   Question: run HillClimbingDemo. Why is it stuck at C with the misleading guess,
    //             although the path S -> B -> E -> G exists?

    return nullptr;  // remove this line when you write TODO 3 (the loop returns by itself)
}

}  // namespace sa2026::algorithms::incomplete_code
