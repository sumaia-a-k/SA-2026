#include "sa2026/problems/incomplete_code/maze/MazeProblem.h"

#include <memory>

#include "sa2026/problems/incomplete_code/maze/MazeAction.h"  // you need it in TODO 2
#include "sa2026/problems/incomplete_code/maze/MazeState.h"

namespace sa2026::problems::incomplete_code::maze {

MazeProblem::MazeProblem(const MazePtr& maze) {
    MazeState::setMaze(maze);  // all states share this one maze

    // TODO 1: create the initial state. The player starts on the start cell.
    //         Hint: initialState = std::make_shared<MazeState>(maze->getStartRow(), maze->getStartCol());

    // TODO 2: add the four actions to the vector "actions".
    //         Hint: actions.push_back(std::make_shared<MazeAction>("Move up", -1, 0));
    //         Use these names and changes (rowChange, colChange):
    //           "Move up"    (-1,  0)
    //           "Move down"  ( 1,  0)
    //           "Move left"  ( 0, -1)
    //           "Move right" ( 0,  1)
    //         The order of this vector is the order the algorithms try the actions.
}

core::StatePtr MazeProblem::getInitialState() const {
    // TODO 3: return the initial state.
    return nullptr;
}

bool MazeProblem::isGoal(const core::StatePtr& state) const {
    // TODO 4: ask the state if it is a goal.
    return false;
}

std::vector<core::ActionPtr> MazeProblem::getActions() const {
    // TODO 5: return the vector of actions.
    return {};
}

// The cost of going from state s to state next using action a.
double MazeProblem::getActionCost(const core::StatePtr& s, const core::ActionPtr& a,
                                  const core::StatePtr& next) const {
    // TODO 6: every step costs the same. Return 1.
    //         Question: what changes if some cells are "mud" and cost 3?
    return 0;
}

}  // namespace sa2026::problems::incomplete_code::maze
