#include "sa2026/problems/maze/MazeAction.h"

#include <memory>

#include "sa2026/problems/maze/MazeState.h"

namespace sa2026::problems::maze {

MazeAction::MazeAction(const std::string& name, int rowChange, int colChange)
    : name(name), rowChange(rowChange), colChange(colChange) {}

std::vector<core::StatePtr> MazeAction::apply(const core::StatePtr& s) const {
    // No type check before: MazeProblem only creates MazeState objects.
    // dynamic_cast checks the type when the program runs. If another state comes here,
    // it is a bug, and the std::bad_cast error shows it fast (like ClassCastException in Java).
    const MazeState& current = dynamic_cast<const MazeState&>(*s);
    int newRow = current.getRow() + rowChange;
    int newCol = current.getCol() + colChange;

    if (!MazeState::getMaze()->isFree(newRow, newCol)) {
        return {};  // the move is not allowed: an empty vector
    }
    // std::make_shared creates the object and gives us a shared pointer to it
    core::StatePtr next = std::make_shared<MazeState>(newRow, newCol);

    // a vector with exactly one item.
    // The result is a vector because in other problems one action can give many states.
    return {next};
}

std::string MazeAction::getName() const {
    return name;
}

}  // namespace sa2026::problems::maze
