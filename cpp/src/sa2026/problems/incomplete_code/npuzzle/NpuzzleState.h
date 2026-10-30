#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "sa2026/core/State.h"

namespace sa2026::problems::incomplete_code::npuzzle {

/*
 * STUDENT TASK: write the bodies in NpuzzleState.cpp.
 * This header is ready. Search for "TODO" in the .cpp file and follow the steps.
 *
 * A state of the N-puzzle = where every tile is.
 *
 * We keep the board in ONE vector, row by row. 0 = the empty cell.
 *   4 1 2
 *   5 8 3    ->  tiles = {4, 1, 2, 5, 8, 3, 7, 6, 0}
 *   7 6 _
 * index = row * n + col,   row = index / n,   col = index % n
 *
 * Goal: {1, 2, 3, ..., n*n-1, 0} (the empty cell at the end).
 *
 * A state never changes after it is created: the fields are const and there are no setters.
 * To make a move, we create a NEW state (see moveEmptyTo).
 */
class NpuzzleState : public core::State {
public:
    // The vector is COPIED into the state (in C++ a vector is copied, not shared like a Java array).
    // So the caller can not change our tiles later.
    explicit NpuzzleState(const std::vector<int>& tiles);

    int getSize() const;  // the board is n x n
    int getTile(int row, int col) const;
    std::vector<int> getTiles() const;  // a copy, so the caller can not change this state
    int getEmptyRow() const;
    int getEmptyCol() const;

    /*
     * Returns a NEW state: the empty cell moves to (row, col),
     * and the tile that was there slides into the old empty cell.
     * MoveEmptyAction checks the border before it calls this.
     */
    core::StatePtr moveEmptyTo(int row, int col) const;

    bool isGoal() const override;
    std::string toString() const override;
    bool equals(const core::State& other) const override;
    std::size_t hashCode() const override;

private:
    // finds the index of the 0 (used once, in the constructor)
    static int findEmpty(const std::vector<int>& tiles);

    const std::vector<int> tiles;  // the board, row by row; 0 = the empty cell
    const int n;                   // the board is n x n
    const int emptyIndex;          // where the 0 is (we find it once, not at every call)
};

}  // namespace sa2026::problems::incomplete_code::npuzzle
