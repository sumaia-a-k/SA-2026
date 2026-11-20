import heapq  # you need it in the TODOs

from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.core.state import State  # you need it in TODO 1 (for the type hint)


class AStar(SearchAlgorithm):
    """
    STUDENT TASK: write the body of search().
    Everything else is ready. Search for "TODO" and follow the steps.
    Check your work with a_star_demo.py (in this folder).

    A* Search.

    A* always expands the node with the smallest f(n) = g(n) + h(n):
      g(n) = the real cost from the start to n (we already paid it)
      h(n) = a guess of the cost from n to the goal

    A* is complete (like UCS, when every cost is more than 0).
    A* is optimal:
      tree search  -> if h is admissible
      graph search -> if h is consistent
    """

    # True = graph search, False = tree search (the default)
    def __init__(self, use_graph_search: bool = False):
        super().__init__(use_graph_search)

    def search(self, p: Problem) -> Node | None:
        self._reset_counters()

        # The code is almost the same as your ucs.py (and your greedy.py).
        # Only f(n), the number the queue sorts by, is different.

        # TODO 1: get the heuristic of the problem:  h = p.get_heuristic_function()
        #         Then, like in UCS: frontier: list[Node] = [] (used with heapq),
        #         explored: set[State] = set()  and  visiting_order = 0

        # TODO 2: create the start node with FIVE values:
        #           Node(start, None, None, 0.0, f)
        #         (start = p.get_initial_state()). Add it with heapq.heappush(frontier, ...)
        #         and count it: self.generated_nodes += 1
        #         Question: what is f(n) of the start node? (g = 0)

        # TODO 3: while the frontier is not empty (while frontier:):
        #   a) take the node with the smallest f(n):  current_node = heapq.heappop(frontier)
        #   b) graph search only: if its state is in explored, skip it with "continue".
        #   c) visiting_order += 1  and  current_node.visiting_order = visiting_order
        #   d) goal test: if p.is_goal(current_node.state), return current_node.
        #      Question: why must we test the goal here, and not when we create the child?
        #   e) graph search only: add the state to explored.
        #   f) expand the node: self.nodes_actually_expanded += 1
        #      then for every action and every next state s (like in UCS):
        #        - path_cost = current_node.path_cost + p.get_action_cost(current_node.state, action, s)
        #        - f = path_cost + h.get_h(s)   <- the only line that makes it A*
        #        - child = Node(s, current_node, action, path_cost, f)
        #        - heapq.heappush(frontier, child)  and count it: self.generated_nodes += 1
        #   Question: what happens if h.get_h(s) is 0 for every state? (a_star_demo.py has a check for it.)

        # TODO 4: the queue is empty and we did not find a goal: return None.
        #   Question: on the "small map" in a_star_demo.py, graph search returns a path of 9 km,
        #             but tree search finds 7 km. The guess is admissible. Why is it not enough?
        return None
