from random import Random

from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm


class StochasticHillClimbing(SearchAlgorithm):
    """
    Stochastic Hill Climbing.

    The same as HillClimbing, but it does not take the BEST neighbour:
    it takes a RANDOM one of the BETTER neighbours (h(neighbour) < h(current)).
    Every better neighbour has the same chance.
    It stops for the same reason: no neighbour is better.

    It usually needs more moves. Two runs with different seeds can end in different places.
    The same seed always gives the same result. (Java and C++ have other random makers,
    so there the same seed can give another result.)
    """

    def __init__(self, seed: int):
        super().__init__()
        self._seed = seed
        self._stuck_node: Node | None = None  # where the last search stopped, when it did not find a goal

    # the node where the last search stopped without a goal (None after a success)
    def get_stuck_node(self) -> Node | None:
        return self._stuck_node

    def search(self, p: Problem) -> Node | None:
        self._reset_counters()
        self._stuck_node = None
        # a new search with the same seed makes the same random choices again
        random = Random(self._seed)
        h = p.get_heuristic_function()
        visiting_order = 0

        start = p.get_initial_state()
        current = Node(start, None, None, 0.0, h.get_h(start))
        self.generated_nodes += 1

        while True:
            visiting_order += 1
            current.visiting_order = visiting_order
            if p.is_goal(current.state):
                return current

            # keep ALL the better neighbours (not only the best one)
            self.nodes_actually_expanded += 1
            better: list[Node] = []
            for action in p.get_actions():
                next_states = action.apply(current.state)
                for s in next_states:
                    path_cost = current.path_cost + p.get_action_cost(current.state, action, s)
                    child = Node(s, current, action, path_cost, h.get_h(s))
                    self.generated_nodes += 1
                    if child.total_cost < current.total_cost:
                        better.append(child)

            # no neighbour is better: stop, we are stuck
            if not better:
                self._stuck_node = current
                return None
            # take a random one of the better neighbours
            current = random.choice(better)
