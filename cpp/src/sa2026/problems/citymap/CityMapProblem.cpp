#include "sa2026/problems/citymap/CityMapProblem.h"

#include <memory>
#include <stdexcept>

#include "sa2026/problems/citymap/CityState.h"
#include "sa2026/problems/citymap/DriveAction.h"

namespace sa2026::problems::citymap {

CityMapProblem::CityMapProblem(const std::string& startCity, const std::string& goalCity,
                               const CityMap& map)
    : map(map) {
    if (!map.hasCity(startCity) || !map.hasCity(goalCity)) {
        throw std::invalid_argument("The start and goal cities must be on the map.");
    }
    CityState::setGoalCity(goalCity);
    initialState = std::make_shared<CityState>(startCity);
    actions.push_back(std::make_shared<DriveAction>(map));
}

core::StatePtr CityMapProblem::getInitialState() const {
    return initialState;
}

bool CityMapProblem::isGoal(const core::StatePtr& state) const {
    return state->isGoal();
}

std::vector<core::ActionPtr> CityMapProblem::getActions() const {
    return actions;
}

double CityMapProblem::getActionCost(const core::StatePtr& s, const core::ActionPtr& a,
                                     const core::StatePtr& next) const {
    const std::string from = dynamic_cast<const CityState&>(*s).getCity();
    const std::string to = dynamic_cast<const CityState&>(*next).getCity();
    return map.getDistance(from, to);
}

}  // namespace sa2026::problems::citymap
