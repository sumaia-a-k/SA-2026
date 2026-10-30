#include "sa2026/problems/incomplete_code/npuzzle/NpuzzleState.h"

#include <cmath>
#include <cstdio>
#include <memory>

namespace sa2026::problems::incomplete_code::npuzzle {

NpuzzleState::NpuzzleState(const std::vector<int>& tiles)
    : tiles(tiles),
      n(static_cast<int>(std::sqrt(tiles.size()))),  // exact: NpuzzleProblem checks that the board is n x n
      emptyIndex(findEmpty(tiles)) {}

int NpuzzleState::findEmpty(const std::vector<int>& tiles) {
    // TODO 1: return the index of the 0 in the tiles (a for loop).
    //         There is only one 0: "return i;" inside the loop stops it at once.
    //         Question: why do we find it once (in the constructor), and not in getEmptyRow() every time?
    return 0;
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
    // TODO 2: change the index of the empty cell into its row. Hint: emptyIndex / n
    return 0;
}

int NpuzzleState::getEmptyCol() const {
    // TODO 3: change the index of the empty cell into its col. Hint: emptyIndex % n
    return 0;
}

core::StatePtr NpuzzleState::moveEmptyTo(int row, int col) const {
    // TODO 4: 1) make a copy of the tiles:  std::vector<int> newTiles = tiles;
    //         2) find the index of (row, col):  row * n + col
    //         3) in the COPY: put the tile from that index into the empty cell,
    //            and put 0 at that index
    //         4) return std::make_shared<NpuzzleState>(newTiles);
    //         Question: "tiles" is const here. What does the compiler say if you try to change it?
    return std::make_shared<NpuzzleState>(tiles);
}

// the tiles are 1, 2, 3, ..., n*n-1 and the last cell is empty
bool NpuzzleState::isGoal() const {
    // TODO 5: for every index i from 0 to tiles.size() - 2:
    //           if tiles[i] is not i + 1, return false.
    //         At the end, return true if the last tile (tiles.back()) is 0.
    return false;
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
    // TODO 6: 1) return true if other is the same object (this == &other)
    //         2) dynamic_cast<const NpuzzleState*>(&other); return false if it gives nullptr
    //         3) compare the two vectors with ==  (it compares the numbers)
    return false;
}

// equal states must give the same number
std::size_t NpuzzleState::hashCode() const {
    // TODO 7: do the same as Arrays.hashCode() in Java:
    //           std::size_t hash = 1;
    //           for every tile:  hash = 31 * hash + tile
    //           return hash;
    //         Question: two different boards can get the same number. Is that a problem?
    return 0;
}

}  // namespace sa2026::problems::incomplete_code::npuzzle
