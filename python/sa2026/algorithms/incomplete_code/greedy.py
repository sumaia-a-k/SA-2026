import heapq  # you need it in the TODOs

from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.core.state import State  # you need it in TODO 1 (for the type hint)


class Greedy(SearchAlgorithm):
    """
    STUDENT TASK: write the body of search().
    Everything else is ready. Search for "TODO" and follow the steps.
    Check your work with greedy_demo.py (in this folder).

    Greedy Best-First Search.

    Greedy always expands the node that LOOKS closest to the goal:
    the node with the smallest guess h(n). So f(n) = h(n).

    Tree search:  can go around a loop forever, even with a good heuristic.
    Graph search: complete (when the number of states is finite).

    Greedy is NOT optimal, with any heuristic. It is often fast.
    """

    # True = graph search, False = tree search (the default)
    def __init__(self, use_graph_search: bool = False):
        super().__init__(use_graph_search)

    def search(self, p: Problem) -> Node | None:
        self._reset_counters()

        # The code is almost the same as your ucs.py. Only f(n), the number the queue sorts by, is different.

        # TODO 1: get the heuristic of the problem:  h = p.get_heuristic_function()
        #         Then, like in UCS: frontier: list[Node] = [] (used with heapq),
        #         explored: set[State] = set()  and  visiting_order = 0
        #         Question: heapq sorts the nodes by total_cost (Node.__lt__()).
        #                   For Greedy, what must total_cost be?

        # TODO 2: create the start node with FIVE values:
        #           Node(start, None, None, 0.0, h.get_h(start))
        #         (start = p.get_initial_state()). Add it with heapq.heappush(frontier, ...)
        #         and count it: self.generated_nodes += 1
        #         Question: UCS used Node(start). Why is it not enough for Greedy?

        # TODO 3: while the frontier is not empty (while frontier:):
        #   a) take the node with the smallest f(n):  current_node = heapq.heappop(frontier)
        #   b) graph search only: if its state is in explored, skip it with "continue".
        #   c) visiting_order += 1  and  current_node.visiting_order = visiting_order
        #   d) goal test: if p.is_goal(current_node.state), return current_node.
        #   e) graph search only: add the state to explored.
        #   f) expand the node: self.nodes_actually_expanded += 1
        #      then for every action and every next state s (like in UCS):
        #        - path_cost = current_node.path_cost + p.get_action_cost(current_node.state, action, s)
        #          Question: Greedy does not use g(n) to choose. Why do we still compute it?
        #        - f = h.get_h(s)       <- the only line that makes it Greedy
        #        - child = Node(s, current_node, action, path_cost, f)
        #        - heapq.heappush(frontier, child)  and count it: self.generated_nodes += 1
        #   Question: run greedy_demo.py. The path on the city map costs 21 km, but 18 km is possible. Why?

        # TODO 4: the queue is empty and we did not find a goal: return None.
        return None
