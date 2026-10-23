#pragma once

#include <memory>
#include <vector>

#include "sa2026/core/HeuristicFunction.h"
#include "sa2026/core/IAction.h"
#include "sa2026/core/Node.h"
#include "sa2026/core/State.h"

namespace sa2026::core {

/*
 * Problem and SearchAlgorithm use each other. If the two headers include each other,
 * we get a circular include. So here we only say "the class SearchAlgorithm exists"
 * (a forward declaration). Problem.cpp includes the full SearchAlgorithm.h.
 */
class SearchAlgorithm;

/*
 * A problem says: where we start, what the goal is,
 * which actions we have, and how much each action costs.
 *
 * For each new problem, write a class that extends Problem.
 */
class Problem {
public:
    virtual ~Problem() = default;

    // the state where the search starts
    virtual StatePtr getInitialState() const = 0;

    // true if the state is a goal state
    virtual bool isGoal(const StatePtr& state) const = 0;

    // all the actions of this problem
    virtual std::vector<ActionPtr> getActions() const = 0;

    // the cost of going from state s to state next using action a
    virtual double getActionCost(const StatePtr& s, const ActionPtr& a, const StatePtr& next) const = 0;

    /*
     * The heuristic used by Greedy and A*.
     * By default a problem has no heuristic, so this method throws an error.
     * Override it if your problem has a heuristic.
     */
    virtual std::shared_ptr<const HeuristicFunction> getHeuristicFunction() const;

    // solves this problem with the given algorithm and returns the goal node (or nullptr)
    NodePtr solve(SearchAlgorithm& algorithm) const;
};

}  // namespace sa2026::core
