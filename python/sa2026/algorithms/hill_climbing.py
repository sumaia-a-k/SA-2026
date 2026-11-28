from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.core.state import State


class HillClimbing(SearchAlgorithm):
    """
    Hill Climbing (steepest): a local search.

    It keeps only ONE state: the current one. No frontier, no explored set.
    At every step it looks at ALL the neighbours, takes the best one (the smallest h),
    and moves there ONLY IF it is better: h(best) < h(current).
    If no neighbour is better, it stops. Same h: the first neighbour wins.

    We minimize h (a distance to the goal, smaller is better).

    search() returns the goal node, or None when it is stuck (it stopped, but not at a goal).
    Then get_stuck_node() gives the state where it stopped: the best state of this climb.

    NOT complete (it can get stuck: local minimum, plateau, ridge). NOT optimal.
    It is NOT tree search and NOT graph search: it has no frontier and no explored set.
    It needs no explored set: h gets smaller at every move, so it can never come back to an old state.
    """

    # no use_graph_search here: Hill Climbing is not tree search and not graph search
    def __init__(self):
        super().__init__()
        self._stuck_node: Node | None = None  # where the last climb stopped, when it did not find a goal

    # the node where the last search stopped without a goal (None after a success)
    def get_stuck_node(self) -> Node | None:
        return self._stuck_node

    def search(self, p: Problem) -> Node | None:
        self._reset_counters()
        return self.climb(p, p.get_initial_state())

    # One climb from the state "start". RandomRestart calls it with random start states.
    # It does not reset the counters, so RandomRestart can count all its climbs together.
    def climb(self, p: Problem, start: State) -> Node | None:
        self._stuck_node = None
        h = p.get_heuristic_function()
        visiting_order = 0

        # the start node: path cost 0, total_cost = h(start)
        current = Node(start, None, None, 0.0, h.get_h(start))
        self.generated_nodes += 1

        while True:
            visiting_order += 1
            current.visiting_order = visiting_order

            # goal test first
            if p.is_goal(current.state):
                return current

            # look at ALL the neighbours and keep the best one
            self.nodes_actually_expanded += 1
            best: Node | None = None
            for action in p.get_actions():
                next_states = action.apply(current.state)
                for s in next_states:
                    path_cost = current.path_cost + p.get_action_cost(current.state, action, s)
                    child = Node(s, current, action, path_cost, h.get_h(s))
                    self.generated_nodes += 1
                    # "<" and not "<=": a later neighbour with the same h does not win
                    if best is None or child.total_cost < best.total_cost:
                        best = child

            # no neighbour is better (or there is no neighbour): stop, we are stuck
            if best is None or best.total_cost >= current.total_cost:
                self._stuck_node = current
                return None
            current = best
