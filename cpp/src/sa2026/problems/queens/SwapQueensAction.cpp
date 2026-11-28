#include "sa2026/problems/queens/SwapQueensAction.h"

#include "sa2026/problems/queens/QueensState.h"

namespace sa2026::problems::queens {

std::vector<core::StatePtr> SwapQueensAction::apply(const core::StatePtr& s) const {
    const QueensState& board = dynamic_cast<const QueensState&>(*s);
    std::vector<core::StatePtr> nextStates;
    for (int i = 0; i < board.getSize(); i++) {
        for (int j = i + 1; j < board.getSize(); j++) {
            nextStates.push_back(board.swap(i, j));
        }
    }
    return nextStates;
}

std::string SwapQueensAction::getName() const {
    return "Swap two queens";
}

}  // namespace sa2026::problems::queens
