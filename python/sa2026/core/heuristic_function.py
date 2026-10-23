from abc import ABC, abstractmethod

from sa2026.core.state import State


class HeuristicFunction(ABC):
    """
    A heuristic is a guess of the cost from a state to the goal.
    It is used by informed algorithms like Greedy and A*.
    """

    # returns h(n): the guessed cost from state s to the goal
    @abstractmethod
    def get_h(self, s: State) -> float:
        pass
