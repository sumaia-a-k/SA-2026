from sa2026.core.state import State


class CityState(State):
    """
    A state of the city map problem = the city where we are now, for example "A".
    """

    # The goal city is NOT part of the state. It is the same for all states.
    # Like the goal word in WordLadderState, it is a class variable: one copy for all states.
    # CityMapProblem sets it once, before the search starts.
    goal_city: str = ""

    def __init__(self, city: str):
        self.city = city  # do not change it after the state is created

    def is_goal(self) -> bool:
        return self.city == CityState.goal_city

    def __str__(self) -> str:
        return self.city

    # two states are equal when they have the same city
    def __eq__(self, other: object) -> bool:
        if self is other:
            return True
        if not isinstance(other, CityState):
            return False
        return self.city == other.city

    def __hash__(self) -> int:
        return hash(self.city)
