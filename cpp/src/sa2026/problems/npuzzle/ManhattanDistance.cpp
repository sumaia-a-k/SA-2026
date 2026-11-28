#include "sa2026/problems/npuzzle/ManhattanDistance.h"

#include <cstdlib>  // std::abs
#include <vector>

#include "sa2026/problems/npuzzle/NpuzzleState.h"

namespace sa2026::problems::npuzzle {

double ManhattanDistance::getH(const core::StatePtr& s) const {
    const NpuzzleState& board = dynamic_cast<const NpuzzleState&>(*s);
    int n = board.getSize();
    std::vector<int> tiles = board.getTiles();
    int sum = 0;
    for (int i = 0; i < static_cast<int>(tiles.size()); i++) {
        int tile = tiles[i];
        if (tile == 0) {
            continue;  // the empty cell is not a tile
        }
        int goalIndex = tile - 1;  // tile 1 belongs at index 0, tile 2 at index 1, ...
        sum += std::abs(i / n - goalIndex / n) + std::abs(i % n - goalIndex % n);
    }
    return sum;
}

}  // namespace sa2026::problems::npuzzle
