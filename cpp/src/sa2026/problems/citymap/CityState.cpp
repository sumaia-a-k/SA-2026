#include "sa2026/problems/citymap/CityState.h"

#include <functional>

namespace sa2026::problems::citymap {

CityState::CityState(const std::string& city) : city(city) {}

void CityState::setGoalCity(const std::string& newGoalCity) {
    goalCity = newGoalCity;
}

std::string CityState::getCity() const {
    return city;
}

bool CityState::isGoal() const {
    return city == goalCity;
}

std::string CityState::toString() const {
    return city;
}

// two states are equal when they have the same city
bool CityState::equals(const core::State& other) const {
    if (this == &other) return true;
    const CityState* o = dynamic_cast<const CityState*>(&other);
    if (o == nullptr) return false;
    return city == o->city;
}

std::size_t CityState::hashCode() const {
    return std::hash<std::string>{}(city);
}

}  // namespace sa2026::problems::citymap
