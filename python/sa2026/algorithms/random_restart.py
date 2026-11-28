from random import Random

from sa2026.algorithms.hill_climbing import HillClimbing
from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm


class RandomRestart(SearchAlgorithm):
    """
    Random-restart Hill Climbing.

    When Hill Climbing is stuck, start again from a NEW RANDOM state.
    Repeat until we find a goal, or until we have done max_climbs climbs.
    (max_climbs is a limit, so the search always stops.)

    The problem must be able to make a random start state (Problem.get_random_state),
    for example 8-queens. On the city map the start is always S, so it does not help there.

    The counters (generated, expanded) count ALL the climbs together.
    The same seed always gives the same random boards.
    """

    def __init__(self, max_climbs: int, seed: int):
        super().__init__()
        if max_climbs < 1:
            raise ValueError(f"max_climbs must be 1 or more, not {max_climbs}.")
        self._max_climbs = max_climbs
        self._seed = seed
        self.climbs = 0  # how many climbs the last search did

    def search(self, p: Problem) -> Node | None:
        self._reset_counters()
        self.climbs = 0
        random = Random(self._seed)
        hill = HillClimbing()  # its counters start at 0

        goal = None
        while self.climbs < self._max_climbs and goal is None:
            start = p.get_random_state(random)
            goal = hill.climb(p, start)
            self.climbs += 1

        # the numbers of all the climbs together
        self.generated_nodes = hill.generated_nodes
        self.nodes_actually_expanded = hill.nodes_actually_expanded
        return goal  # None: no goal after max_climbs climbs
