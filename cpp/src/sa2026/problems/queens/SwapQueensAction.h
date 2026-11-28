#pragma once

#include <string>
#include <vector>

#include "sa2026/core/IAction.h"
#include "sa2026/core/State.h"

namespace sa2026::problems::queens {

/*
 * The only action of the 8-queens problem: SWAP two queens.
 * The queen of column i takes the row of the queen of column j, and the other way.
 * After a swap there is still one queen in every row and every column.
 * (Moving ONE queen alone would put two queens in the same row.)
 *
 * Like DriveAction, this one action gives MANY next states:
 * all the pairs i < j: 8 x 7 / 2 = 28 neighbours.
 * The order: swap(0,1), swap(0,2), ..., swap(0,7), swap(1,2), ...
 * (the same order as on the lesson page: 1-2, 1-3, ..., 2-3, ...)
 */
class SwapQueensAction : public core::IAction {
public:
    std::vector<core::StatePtr> apply(const core::StatePtr& s) const override;
    std::string getName() const override;
};

}  // namespace sa2026::problems::queens
