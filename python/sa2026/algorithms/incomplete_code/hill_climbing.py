from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.core.state import State


class HillClimbing(SearchAlgorithm):
    """
    STUDENT TASK: write the body of climb().
    Everything else is ready. Search for "TODO" and follow the steps.
    Check your work with hill_climbing_demo.py (in this folder).

    Hill Climbing (steepest): a local search.

    It keeps only ONE state: the current one. No frontier, no explored set.
    At every step it looks at ALL the neighbours, takes the best one (the smallest h),
    and moves there ONLY IF it is better: h(best) < h(current).
    If no neighbour is better, it stops. Same h: the first neighbour wins.

    search() returns the goal node, or None when it is stuck.
    Then get_stuck_node() gives the state where it stopped.
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

    # one climb from the state "start"
    def climb(self, p: Problem, start: State) -> Node | None:
        self._stuck_node = None

        # TODO 1: get the heuristic: h = p.get_heuristic_function()
        #         and visiting_order = 0.
        #         Question: Hill Climbing has no frontier and no explored set. What does it keep?

        # TODO 2: create the current node with FIVE values (like in Greedy):
        #           current = Node(start, None, None, 0.0, h.get_h(start))
        #         and count it: self.generated_nodes += 1

        # TODO 3: while True:
        #   a) visiting_order += 1  and  current.visiting_order = visiting_order
        #   b) goal test: if p.is_goal(current.state), return current.
        #   c) look at ALL the neighbours: self.nodes_actually_expanded += 1
        #      best = None
        #      for every action and every next state s (like in Greedy):
        #        - path_cost = current.path_cost + p.get_action_cost(current.state, action, s)
        #        - child = Node(s, current, action, path_cost, h.get_h(s))
        #        - count it: self.generated_nodes += 1
        #        - keep the best one: if best is None or child.total_cost < best.total_cost: best = child
        #          Question: why "<" and not "<="? Which neighbour wins when two have the same h?
        #   d) stop if no neighbour is better:
        #        if best is None or best.total_cost >= current.total_cost:
        #            self._stuck_node = current;  return None
        #      Question: why ">=" and not ">"? What happens on a flat place if we use ">"?
        #   e) move: current = best
        #   Question: run hill_climbing_demo.py. Why is it stuck at C with the misleading guess,
        #             although the path S -> B -> E -> G exists?

        return None  # remove this line when you write TODO 3 (the loop returns by itself)
