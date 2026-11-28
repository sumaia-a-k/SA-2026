#include "sa2026/problems/queens/DiagonalAttacks.h"

#include "sa2026/problems/queens/QueensState.h"

namespace sa2026::problems::queens {

double DiagonalAttacks::getH(const core::StatePtr& s) const {
    const QueensState& board = dynamic_cast<const QueensState&>(*s);
    return board.countAttackingPairs();
}

}  // namespace sa2026::problems::queens
