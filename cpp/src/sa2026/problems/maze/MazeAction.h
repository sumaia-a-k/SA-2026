#pragma once

#include <string>
#include <vector>

#include "sa2026/core/IAction.h"
#include "sa2026/core/State.h"

namespace sa2026::problems::maze {

/*
 * One move of the player: up, down, left or right.
 *
 * All four moves work the same way, only the direction is different.
 * So we use one class and give it the direction (rowChange, colChange).
 * From this one class we create four action objects (see MazeProblem):
 *   ActionPtr moveUp    = std::make_shared<MazeAction>("Move up",    -1,  0);
 *   ActionPtr moveDown  = std::make_shared<MazeAction>("Move down",   1,  0);
 *   ActionPtr moveLeft  = std::make_shared<MazeAction>("Move left",   0, -1);
 *   ActionPtr moveRight = std::make_shared<MazeAction>("Move right",  0,  1);
 */
class MazeAction : public core::IAction {
public:
    MazeAction(const std::string& name, int rowChange, int colChange);

    // moves the player one cell; returns no state if the new cell is a wall or outside
    std::vector<core::StatePtr> apply(const core::StatePtr& s) const override;

    std::string getName() const override;

private:
    const std::string name;
    const int rowChange;  // how much the row changes: -1, 0 or +1
    const int colChange;  // how much the column changes: -1, 0 or +1
};

}  // namespace sa2026::problems::maze
