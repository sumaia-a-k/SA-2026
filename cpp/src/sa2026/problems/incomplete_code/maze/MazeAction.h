#pragma once

#include <string>
#include <vector>

#include "sa2026/core/IAction.h"
#include "sa2026/core/State.h"

namespace sa2026::problems::incomplete_code::maze {

/*
 * STUDENT TASK: finish this class (here and in MazeAction.cpp).
 *
 * One move of the player: up, down, left or right.
 * All four moves work the same way, only the direction is different.
 * So we use ONE class and give it the direction (rowChange, colChange).
 * From this one class we create four action objects (in MazeProblem), for example:
 *   ActionPtr moveUp = std::make_shared<MazeAction>("Move up", -1, 0);
 *
 * Search for "TODO" and follow the steps.
 */
class MazeAction : public core::IAction {
public:
    // TODO 2: declare the constructor MazeAction(const std::string& name, int rowChange, int colChange).
    //         Write its body in MazeAction.cpp.


    // Moves the player one cell. Returns no state if the new cell is a wall or outside.
    std::vector<core::StatePtr> apply(const core::StatePtr& s) const override;

    std::string getName() const override;

private:
    // TODO 1: add three const fields:
    //         name (std::string), rowChange (int), colChange (int)
    //         rowChange and colChange are -1, 0 or +1.
    //         Example: "Move up" -> rowChange = -1, colChange = 0

};

}  // namespace sa2026::problems::incomplete_code::maze
