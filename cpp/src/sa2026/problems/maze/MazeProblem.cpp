#include "sa2026/problems/maze/MazeProblem.h"

#include <memory>

#include "sa2026/problems/maze/MazeAction.h"
#include "sa2026/problems/maze/MazeState.h"

namespace sa2026::problems::maze {

MazeProblem::MazeProblem(const MazePtr& maze) {
    MazeState::setMaze(maze);  // all states share this one maze
    initialState = std::make_shared<MazeState>(maze->getStartRow(), maze->getStartCol());

    // the order of this vector is the order the algorithms try the actions
    actions.push_back(std::make_shared<MazeAction>("Move up", -1, 0));
    actions.push_back(std::make_shared<MazeAction>("Move down", 1, 0));
    actions.push_back(std::make_shared<MazeAction>("Move left", 0, -1));
    actions.push_back(std::make_shared<MazeAction>("Move right", 0, 1));
}

core::StatePtr MazeProblem::getInitialState() const {
    return initialState;
}

bool MazeProblem::isGoal(const core::StatePtr& state) const {
    return state->isGoal();
}

std::vector<core::ActionPtr> MazeProblem::getActions() const {
    return actions;
}

// every step costs the same
double MazeProblem::getActionCost(const core::StatePtr& s, const core::ActionPtr& a,
                                  const core::StatePtr& next) const {
    return 1;
}

}  // namespace sa2026::problems::maze
