#include "sa2026/problems/incomplete_code/npuzzle/NpuzzleProblem.h"

#include <cmath>
#include <memory>
#include <stdexcept>
#include <string>

#include "sa2026/problems/incomplete_code/npuzzle/MoveEmptyAction.h"
#include "sa2026/problems/incomplete_code/npuzzle/NpuzzleState.h"

namespace sa2026::problems::incomplete_code::npuzzle {

NpuzzleProblem::NpuzzleProblem(const std::vector<int>& tiles) {
    check(tiles);

    // TODO 1: create the initial state from the tiles.
    //         Hint: initialState = std::make_shared<NpuzzleState>(tiles);

    // TODO 2: add the four actions to the vector "actions" (actions.push_back(...)).
    //         Use these names and changes of the EMPTY cell (rowChange, colChange):
    //           "Move empty up"    (-1,  0)
    //           "Move empty down"  ( 1,  0)
    //           "Move empty left"  ( 0, -1)
    //           "Move empty right" ( 0,  1)
    //         Hint: std::make_shared<MoveEmptyAction>("Move empty up", -1, 0)
    //         The order of this vector is the order the algorithms try the actions.
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
    // TODO 7 (a bit harder): count the inversions.
    //   For every i, and every j > i: if tiles[i] and tiles[j] are not 0
    //   and tiles[i] > tiles[j], it is one inversion.
    //   Then use the rules in NpuzzleProblem.h.
    //   n = static_cast<int>(std::sqrt(tiles.size()))
    //   Check: {1, 2, 3, 4, 5, 6, 8, 7, 0} has 1 inversion, so it can NOT be solved.
    //   Question: why does a move left or right never change the number of inversions?
    return true;
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
    // TODO 3: return the initial state.
    return nullptr;
}

bool NpuzzleProblem::isGoal(const core::StatePtr& state) const {
    // TODO 4: ask the state if it is a goal.
    return false;
}

std::vector<core::ActionPtr> NpuzzleProblem::getActions() const {
    // TODO 5: return the vector of actions.
    return {};
}

// The cost of going from state s to state next using action a.
double NpuzzleProblem::getActionCost(const core::StatePtr& s, const core::ActionPtr& a,
                                     const core::StatePtr& next) const {
    // TODO 6: every move costs the same. Return 1.
    return 0;
}

}  // namespace sa2026::problems::incomplete_code::npuzzle
