#include "sa2026/problems/queens/QueensProblem.h"

#include <algorithm>  // std::sort, std::shuffle
#include <stdexcept>
#include <string>

#include "sa2026/problems/queens/DiagonalAttacks.h"
#include "sa2026/problems/queens/QueensState.h"
#include "sa2026/problems/queens/SwapQueensAction.h"

namespace sa2026::problems::queens {

QueensProblem::QueensProblem(const std::vector<int>& rows) {
    check(rows);
    initialState = std::make_shared<QueensState>(rows);
    size = static_cast<int>(rows.size());
    actions.push_back(std::make_shared<SwapQueensAction>());
    heuristic = std::make_shared<DiagonalAttacks>();
}

QueensProblem QueensProblem::example1() {
    return QueensProblem({0, 1, 3, 4, 5, 2, 7, 6});
}

QueensProblem QueensProblem::example2() {
    return QueensProblem({0, 1, 2, 5, 6, 7, 4, 3});
}

void QueensProblem::check(const std::vector<int>& rows) {
    if (rows.empty()) {
        throw std::invalid_argument("The board needs at least one queen.");
    }
    std::vector<int> sorted = rows;
    std::sort(sorted.begin(), sorted.end());
    for (int i = 0; i < static_cast<int>(sorted.size()); i++) {
        if (sorted[i] != i) {
            throw std::invalid_argument("Each row from 0 to " + std::to_string(rows.size() - 1)
                                        + " must have exactly one queen.");
        }
    }
}

core::StatePtr QueensProblem::getInitialState() const {
    return initialState;
}

bool QueensProblem::isGoal(const core::StatePtr& state) const {
    return state->isGoal();
}

std::vector<core::ActionPtr> QueensProblem::getActions() const {
    return actions;
}

// every swap costs the same
double QueensProblem::getActionCost(const core::StatePtr& s, const core::ActionPtr& a,
                                    const core::StatePtr& next) const {
    return 1;
}

std::shared_ptr<const core::HeuristicFunction> QueensProblem::getHeuristicFunction() const {
    return heuristic;
}

core::StatePtr QueensProblem::getRandomState(std::mt19937& random) const {
    std::vector<int> rows(size);
    for (int i = 0; i < size; i++) {
        rows[i] = i;
    }
    // mix the rows, like shuffling cards
    std::shuffle(rows.begin(), rows.end(), random);
    return std::make_shared<QueensState>(rows);
}

}  // namespace sa2026::problems::queens
