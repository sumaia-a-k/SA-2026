#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "sa2026/core/State.h"

namespace sa2026::problems::queens {

/*
 * A state of the 8-queens problem = where the queens are.
 *
 * There is ONE queen in every column AND in every row, always.
 * rows[c] = the row of the queen in column c (0 = the top row).
 *   rows = {0, 4, 7, 5, 2, 6, 1, 3}  ->  the queen of column 0 is in row 0,
 *                                        the queen of column 1 is in row 4, ...
 * So two queens can never share a row or a column. Only a DIAGONAL can be a problem.
 *
 * A state never changes after it is created. To move, we create a NEW state (see swap).
 */
class QueensState : public core::State {
public:
    // the vector is COPIED into the state, so the caller can not change our queens later
    explicit QueensState(const std::vector<int>& rows);

    int getSize() const;  // the board is n x n (8 for 8-queens)
    int getRow(int col) const;

    // a NEW state: the queens of column i and column j change their rows
    core::StatePtr swap(int i, int j) const;

    /*
     * The number of PAIRS of queens on the same diagonal.
     * Two queens are on the same diagonal when the row distance = the column distance.
     * We count a pair even if another queen stands between them.
     */
    int countAttackingPairs() const;

    bool isGoal() const override;  // no two queens attack each other
    std::string toString() const override;
    bool equals(const core::State& other) const override;
    std::size_t hashCode() const override;

private:
    const std::vector<int> rows;  // rows[c] = the row of the queen in column c
};

}  // namespace sa2026::problems::queens
