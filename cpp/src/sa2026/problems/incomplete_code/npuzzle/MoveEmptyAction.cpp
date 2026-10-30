#include "sa2026/problems/incomplete_code/npuzzle/MoveEmptyAction.h"

#include "sa2026/problems/incomplete_code/npuzzle/NpuzzleState.h"

namespace sa2026::problems::incomplete_code::npuzzle {

// TODO 1 and 2: give the const fields their values in the initializer list:
//               : name(name), rowChange(rowChange), colChange(colChange) {}
//               (const fields can get a value only there)
MoveEmptyAction::MoveEmptyAction(const std::string& name, int rowChange, int colChange)
    : name(""), rowChange(0), colChange(0) {}

std::vector<core::StatePtr> MoveEmptyAction::apply(const core::StatePtr& s) const {
    // TODO 3: change s into an NpuzzleState:
    //           const NpuzzleState& current = dynamic_cast<const NpuzzleState&>(*s);
    // TODO 4: find the new row and col of the empty cell:
    //         current.getEmptyRow() + rowChange, current.getEmptyCol() + colChange
    // TODO 5: n = current.getSize(). If the new row or col is outside 0 .. n-1:
    //           return {};   (an empty vector)
    //         Else: return {current.moveEmptyTo(newRow, newCol)};
    //         Question: why is there no wall check here, like in the maze?
    return {};
}

std::string MoveEmptyAction::getName() const {
    // TODO 6: return the name.
    return "";
}

}  // namespace sa2026::problems::incomplete_code::npuzzle
