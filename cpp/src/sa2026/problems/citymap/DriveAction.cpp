#include "sa2026/problems/citymap/DriveAction.h"

#include <memory>

#include "sa2026/problems/citymap/CityState.h"

namespace sa2026::problems::citymap {

DriveAction::DriveAction(const CityMap& map) : map(map) {}

std::vector<core::StatePtr> DriveAction::apply(const core::StatePtr& s) const {
    std::string city = dynamic_cast<const CityState&>(*s).getCity();
    std::vector<core::StatePtr> nextStates;
    for (const std::string& neighbor : map.getNeighbors(city)) {
        nextStates.push_back(std::make_shared<CityState>(neighbor));
    }
    return nextStates;
}

std::string DriveAction::getName() const {
    return "Drive to a neighbor city";
}

}  // namespace sa2026::problems::citymap
