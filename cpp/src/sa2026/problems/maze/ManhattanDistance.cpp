#include "sa2026/problems/maze/ManhattanDistance.h"

#include <cstdlib>  // std::abs

#include "sa2026/problems/maze/MazeState.h"

namespace sa2026::problems::maze {

double ManhattanDistance::getH(const core::StatePtr& s) const {
    const MazeState& player = dynamic_cast<const MazeState&>(*s);
    MazePtr maze = MazeState::getMaze();
    return std::abs(player.getRow() - maze->getGoalRow())
           + std::abs(player.getCol() - maze->getGoalCol());
}

}  // namespace sa2026::problems::maze
