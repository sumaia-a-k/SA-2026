from abc import ABC, abstractmethod
from typing import TYPE_CHECKING

from sa2026.core.heuristic_function import HeuristicFunction
from sa2026.core.i_action import IAction
from sa2026.core.node import Node
from sa2026.core.state import State

# Problem and SearchAlgorithm use each other. A normal import here would make a
# "circular import" error. TYPE_CHECKING is False when the program runs, so this
# import is read only by the editor (for the type hint), never by Python.
if TYPE_CHECKING:
    from sa2026.core.search_algorithm import SearchAlgorithm


class Problem(ABC):
    """
    A problem says: where we start, what the goal is,
    which actions we have, and how much each action costs.

    For each new problem, write a class that extends Problem.
    """

    # the state where the search starts
    @abstractmethod
    def get_initial_state(self) -> State:
        pass

    # True if the state is a goal state
    @abstractmethod
    def is_goal(self, state: State) -> bool:
        pass

    # all the actions of this problem
    @abstractmethod
    def get_actions(self) -> list[IAction]:
        pass

    # the cost of going from state s to state next_state using action a
    @abstractmethod
    def get_action_cost(self, s: State, a: IAction, next_state: State) -> float:
        pass

    # The heuristic used by Greedy and A*.
    # By default a problem has no heuristic, so this method raises an error.
    # Override it if your problem has a heuristic.
    def get_heuristic_function(self) -> HeuristicFunction:
        raise NotImplementedError("This problem does not have a heuristic function.")

    # solves this problem with the given algorithm and returns the goal node (or None)
    def solve(self, algorithm: "SearchAlgorithm") -> Node | None:
        return algorithm.search(self)
