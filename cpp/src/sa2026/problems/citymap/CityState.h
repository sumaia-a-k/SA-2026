#pragma once

#include <cstddef>
#include <string>

#include "sa2026/core/State.h"

namespace sa2026::problems::citymap {

/*
 * A state of the city map problem = the city where we are now, for example "A".
 */
class CityState : public core::State {
public:
    explicit CityState(const std::string& city);

    static void setGoalCity(const std::string& newGoalCity);

    std::string getCity() const;

    bool isGoal() const override;
    std::string toString() const override;
    bool equals(const core::State& other) const override;
    std::size_t hashCode() const override;

private:
    /*
     * The goal city is NOT part of the state. It is the same for all states.
     * Like the goal word in WordLadderState, it is static: one copy for all states.
     * CityMapProblem sets it once, before the search starts.
     */
    inline static std::string goalCity;

    const std::string city;
};

}  // namespace sa2026::problems::citymap
