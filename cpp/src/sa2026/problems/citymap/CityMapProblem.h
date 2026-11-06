#pragma once

#include <string>
#include <vector>

#include "sa2026/core/IAction.h"
#include "sa2026/core/Problem.h"
#include "sa2026/core/State.h"
#include "sa2026/problems/citymap/CityMap.h"

namespace sa2026::problems::citymap {

/*
 * The city map problem: drive from the start city to the goal city
 * with the SHORTEST total distance (not the fewest roads!).
 *
 * Example: S -> A -> C -> F -> G  (4 roads, 18 km)
 *     and  S -> A -> D -> G       (3 roads, 33 km)
 *
 * Initial state: the start city.
 * Goal:          the goal city.
 * Actions:       drive to a neighbor city (only one action, but it gives many states).
 * Cost:          the length of the road. Roads have DIFFERENT costs,
 *                so this is a problem for UCS, not for BFS.
 */
class CityMapProblem : public core::Problem {
public:
    CityMapProblem(const std::string& startCity, const std::string& goalCity, const CityMap& map);

    core::StatePtr getInitialState() const override;
    bool isGoal(const core::StatePtr& state) const override;
    std::vector<core::ActionPtr> getActions() const override;

    // the cost of the action = the length of the road between the two cities
    double getActionCost(const core::StatePtr& s, const core::ActionPtr& a,
                         const core::StatePtr& next) const override;

private:
    const CityMap map;
    core::StatePtr initialState;
    std::vector<core::ActionPtr> actions;
};

}  // namespace sa2026::problems::citymap
