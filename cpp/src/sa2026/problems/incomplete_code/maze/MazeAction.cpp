#include "sa2026/problems/incomplete_code/maze/MazeAction.h"

#include <memory>

#include "sa2026/problems/incomplete_code/maze/MazeState.h"  // you need it in TODO 3 and TODO 5

namespace sa2026::problems::incomplete_code::maze {

// TODO 2: write the constructor MazeAction::MazeAction(const std::string& name, int rowChange, int colChange).
//         Hint: const fields get their value in the initializer list:  : name(name), ... {}


// Moves the player one cell. Returns no state if the new cell is a wall or outside.
std::vector<core::StatePtr> MazeAction::apply(const core::StatePtr& s) const {
    // TODO 3: cast s to MazeState:  const MazeState& current = dynamic_cast<const MazeState&>(*s);
    //         No type check is needed before: MazeProblem only creates MazeState objects.
    //         Question: what happens if someone passes another kind of state?
    // TODO 4: find the new row and the new col (current position + the changes).
    // TODO 5: ask the maze if the new cell is free. Hint: MazeState::getMaze()->isFree(...)
    //         - if NOT free: return {};   (an empty vector)
    //         - if free:     create a new state:  core::StatePtr next = std::make_shared<MazeState>(...);
    //                        and return it inside a vector:  return {next};
    //
    // Important: do NOT change the old state. Always create a new one.
    return {};
}

std::string MazeAction::getName() const {
    // TODO 6: return the name.
    return "";
}

}  // namespace sa2026::problems::incomplete_code::maze
