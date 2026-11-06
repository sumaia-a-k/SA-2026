from sa2026.core.i_action import IAction
from sa2026.core.problem import Problem
from sa2026.core.state import State
from sa2026.problems.citymap.city_map import CityMap
from sa2026.problems.citymap.city_state import CityState
from sa2026.problems.citymap.drive_action import DriveAction


class CityMapProblem(Problem):
    """
    The city map problem: drive from the start city to the goal city
    with the SHORTEST total distance (not the fewest roads!).

    Example: S -> A -> C -> F -> G  (4 roads, 18 km)
        and  S -> A -> D -> G       (3 roads, 33 km)

    Initial state: the start city.
    Goal:          the goal city.
    Actions:       drive to a neighbor city (only one action, but it gives many states).
    Cost:          the length of the road. Roads have DIFFERENT costs,
                   so this is a problem for UCS, not for BFS.
    """

    def __init__(self, start_city: str, goal_city: str, city_map: CityMap):
        if not city_map.has_city(start_city) or not city_map.has_city(goal_city):
            raise ValueError("The start and goal cities must be on the map.")
        self._city_map = city_map
        CityState.goal_city = goal_city
        self._initial_state = CityState(start_city)
        self._actions: list[IAction] = [DriveAction(city_map)]

    def get_initial_state(self) -> State:
        return self._initial_state

    def is_goal(self, state: State) -> bool:
        return state.is_goal()

    def get_actions(self) -> list[IAction]:
        return self._actions

    # the cost of the action = the length of the road between the two cities
    def get_action_cost(self, s: State, a: IAction, next_state: State) -> float:
        # float(): the road length is an int (10), the cost is a float (10.0), like in Java
        return float(self._city_map.get_distance(s.city, next_state.city))
