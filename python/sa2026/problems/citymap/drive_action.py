from sa2026.core.i_action import IAction
from sa2026.core.state import State
from sa2026.problems.citymap.city_map import CityMap
from sa2026.problems.citymap.city_state import CityState


class DriveAction(IAction):
    """
    The only action of the problem: drive on ONE road to a neighbor city.
    Like ChangeLetterAction, this one action can give MANY next states:
      "A" -> "C", "D", "S"

    The action does not know the cost. The cost (the road length)
    comes from CityMapProblem.get_action_cost().
    """

    def __init__(self, city_map: CityMap):
        self._city_map = city_map

    def apply(self, s: State) -> list[State]:
        next_states: list[State] = []
        for neighbor in self._city_map.get_neighbors(s.city):
            next_states.append(CityState(neighbor))
        return next_states

    def get_name(self) -> str:
        return "Drive to a neighbor city"
