#pragma once

#include <string>
#include <vector>

#include "sa2026/core/IAction.h"
#include "sa2026/core/State.h"
#include "sa2026/problems/citymap/CityMap.h"

namespace sa2026::problems::citymap {

/*
 * The only action of the problem: drive on ONE road to a neighbor city.
 * Like ChangeLetterAction, this one action can give MANY next states:
 *   "A" -> "C", "D", "S"
 *
 * The action does not know the cost. The cost (the road length)
 * comes from CityMapProblem::getActionCost().
 */
class DriveAction : public core::IAction {
public:
    explicit DriveAction(const CityMap& map);

    std::vector<core::StatePtr> apply(const core::StatePtr& s) const override;
    std::string getName() const override;

private:
    // our own copy of the map (like the dictionary in ChangeLetterAction); the map is small
    const CityMap map;
};

}  // namespace sa2026::problems::citymap
