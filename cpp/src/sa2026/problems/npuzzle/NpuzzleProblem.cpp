#include "sa2026/problems/npuzzle/NpuzzleProblem.h"

#include <cmath>
#include <memory>
#include <stdexcept>
#include <string>

#include "sa2026/problems/npuzzle/MoveEmptyAction.h"
#include "sa2026/problems/npuzzle/NpuzzleState.h"

namespace sa2026::problems::npuzzle {

NpuzzleProblem::NpuzzleProblem(const std::vector<int>& tiles) {
    check(tiles);
    initialState = std::make_shared<NpuzzleState>(tiles);

    // the order of this vector is the order the algorithms try the actions
    actions.push_back(std::make_shared<MoveEmptyAction>("Move empty up", -1, 0));
    actions.push_back(std::make_shared<MoveEmptyAction>("Move empty down", 1, 0));
    actions.push_back(std::make_shared<MoveEmptyAction>("Move empty left", 0, -1));
    actions.push_back(std::make_shared<MoveEmptyAction>("Move empty right", 0, 1));
}

NpuzzleProblem NpuzzleProblem::easy() {
    return NpuzzleProblem({1, 2, 3, 4, 0, 5, 7, 8, 6});
}

NpuzzleProblem NpuzzleProblem::medium() {
    return NpuzzleProblem({4, 1, 2, 5, 8, 3, 7, 6, 0});
}

NpuzzleProblem NpuzzleProblem::hard() {
    return NpuzzleProblem({1, 8, 3, 2, 6, 4, 7, 0, 5});
}

bool NpuzzleProblem::isSolvable(const std::vector<int>& tiles) {
    int n = static_cast<int>(std::sqrt(tiles.size()));
    int size = static_cast<int>(tiles.size());
    int inversions = 0;
    int emptyIndex = 0;
    for (int i = 0; i < size; i++) {
        if (tiles[i] == 0) {
            emptyIndex = i;
            continue;
        }
        for (int j = i + 1; j < size; j++) {
            if (tiles[j] != 0 && tiles[i] > tiles[j]) {
                inversions++;
            }
        }
    }
    if (n % 2 == 1) {
        return inversions % 2 == 0;
    }
    int emptyRowFromBottom = n - emptyIndex / n;
    return (inversions + emptyRowFromBottom) % 2 == 1;
}

void NpuzzleProblem::check(const std::vector<int>& tiles) {
    int size = static_cast<int>(tiles.size());
    int n = static_cast<int>(std::sqrt(size));
    if (n < 2 || n * n != size) {
        throw std::invalid_argument("The board must be n x n (4, 9, 16, ... numbers), not "
                                    + std::to_string(size) + " numbers.");
    }
    std::vector<bool> seen(size, false);
    for (int t : tiles) {
        if (t < 0 || t >= size || seen[t]) {
            throw std::invalid_argument("Each number from 0 to " + std::to_string(size - 1)
                                        + " must be on the board once.");
        }
        seen[t] = true;
    }
    if (!isSolvable(tiles)) {
        throw std::invalid_argument("This board can never be solved (see isSolvable()).");
    }
}

core::StatePtr NpuzzleProblem::getInitialState() const {
    return initialState;
}

bool NpuzzleProblem::isGoal(const core::StatePtr& state) const {
    return state->isGoal();
}

std::vector<core::ActionPtr> NpuzzleProblem::getActions() const {
    return actions;
}

// every move costs the same
double NpuzzleProblem::getActionCost(const core::StatePtr& s, const core::ActionPtr& a,
                                     const core::StatePtr& next) const {
    return 1;
}

}  // namespace sa2026::problems::npuzzle
