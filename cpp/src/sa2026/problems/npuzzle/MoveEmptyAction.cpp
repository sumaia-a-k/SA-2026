#include "sa2026/problems/npuzzle/MoveEmptyAction.h"

#include "sa2026/problems/npuzzle/NpuzzleState.h"

namespace sa2026::problems::npuzzle {

MoveEmptyAction::MoveEmptyAction(const std::string& name, int rowChange, int colChange)
    : name(name), rowChange(rowChange), colChange(colChange) {}

std::vector<core::StatePtr> MoveEmptyAction::apply(const core::StatePtr& s) const {
    const NpuzzleState& current = dynamic_cast<const NpuzzleState&>(*s);
    int newRow = current.getEmptyRow() + rowChange;
    int newCol = current.getEmptyCol() + colChange;
    int n = current.getSize();

    if (newRow < 0 || newRow >= n || newCol < 0 || newCol >= n) {
        return {};  // outside the board: the move is not allowed
    }
    return {current.moveEmptyTo(newRow, newCol)};
}

std::string MoveEmptyAction::getName() const {
    return name;
}

}  // namespace sa2026::problems::npuzzle
