#include "sa2026/problems/npuzzle/NpuzzleState.h"

#include <cmath>
#include <cstdio>
#include <memory>

namespace sa2026::problems::npuzzle {

NpuzzleState::NpuzzleState(const std::vector<int>& tiles)
    : tiles(tiles),
      n(static_cast<int>(std::sqrt(tiles.size()))),  // exact: NpuzzleProblem checks that the board is n x n
      emptyIndex(findEmpty(tiles)) {}

int NpuzzleState::findEmpty(const std::vector<int>& tiles) {
    for (std::size_t i = 0; i < tiles.size(); i++) {
        if (tiles[i] == 0) {
            return static_cast<int>(i);  // there is only one 0, so we can stop here
        }
    }
    return -1;
}

int NpuzzleState::getSize() const {
    return n;
}

int NpuzzleState::getTile(int row, int col) const {
    return tiles[row * n + col];
}

std::vector<int> NpuzzleState::getTiles() const {
    return tiles;  // returns a copy
}

int NpuzzleState::getEmptyRow() const {
    return emptyIndex / n;
}

int NpuzzleState::getEmptyCol() const {
    return emptyIndex % n;
}

core::StatePtr NpuzzleState::moveEmptyTo(int row, int col) const {
    std::vector<int> newTiles = tiles;        // never change this state: work on a copy
    int target = row * n + col;
    newTiles[emptyIndex] = newTiles[target];  // the tile slides into the empty cell
    newTiles[target] = 0;                     // its old cell is empty now
    return std::make_shared<NpuzzleState>(newTiles);
}

// the tiles are 1, 2, 3, ..., n*n-1 and the last cell is empty
bool NpuzzleState::isGoal() const {
    for (std::size_t i = 0; i + 1 < tiles.size(); i++) {
        if (tiles[i] != static_cast<int>(i) + 1) {
            return false;
        }
    }
    return tiles.back() == 0;
}

// draws the board; "_" = the empty cell
std::string NpuzzleState::toString() const {
    std::string text;
    for (std::size_t i = 0; i < tiles.size(); i++) {
        if (tiles[i] == 0) {
            text += "  _";
        } else {
            char cell[8];
            std::snprintf(cell, sizeof(cell), "%3d", tiles[i]);  // like String.format("%3d") in Java
            text += cell;
        }
        if ((i + 1) % n == 0) {
            text += '\n';
        }
    }
    return text;
}

// two states are equal when all the tiles are in the same places
bool NpuzzleState::equals(const core::State& other) const {
    if (this == &other) return true;
    const NpuzzleState* o = dynamic_cast<const NpuzzleState*>(&other);
    if (o == nullptr) return false;
    return tiles == o->tiles;  // == on two vectors compares the numbers
}

/*
 * The same as Arrays.hashCode() in Java: mix all the tiles with the prime 31.
 * Two different boards can get the same number (a conflict). It is rare,
 * and then equals() decides.
 */
std::size_t NpuzzleState::hashCode() const {
    std::size_t hash = 1;
    for (int tile : tiles) {
        hash = 31 * hash + static_cast<std::size_t>(tile);
    }
    return hash;
}

}  // namespace sa2026::problems::npuzzle
