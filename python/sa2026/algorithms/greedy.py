import heapq

from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.core.state import State


class Greedy(SearchAlgorithm):
    """
    Greedy Best-First Search.

    Greedy always expands the node that LOOKS closest to the goal:
    the node with the smallest guess h(n). So f(n) = h(n).

    The code is the same as UCS. Only f(n), the number the queue sorts by, is different:
      UCS:    f(n) = g(n)   the real cost so far
      Greedy: f(n) = h(n)   the guess to the goal
    We still compute g(n) (path_cost), but only to know the cost of the path at the end.

    Tree search:  can go around a loop forever, even with a good heuristic.
    Graph search: complete (when the number of states is finite).

    Greedy is NOT optimal, with any heuristic. It is often fast.
    """

    # True = graph search, False = tree search (the default)
    def __init__(self, use_graph_search: bool = False):
        super().__init__(use_graph_search)

    def search(self, p: Problem) -> Node | None:
        self._reset_counters()

        # the guess h(n) of this problem (raises an error if the problem has no heuristic)
        h = p.get_heuristic_function()

        # heapq uses Node.__lt__(): the node with the smallest total_cost comes first.
        # Here total_cost = f(n), and we give it to Node(...) ourselves.
        frontier: list[Node] = []
        explored: set[State] = set()  # set: "in" is fast
        visiting_order = 0

        # the start node: path cost 0, f(n) = h(n)
        start = p.get_initial_state()
        start_node = Node(start, None, None, 0.0, h.get_h(start))
        heapq.heappush(frontier, start_node)
        self.generated_nodes += 1  # the start node is a generated node too

        while frontier:  # while the queue is not empty
            # take the node with the smallest f(n)
            current_node = heapq.heappop(frontier)

            # graph search: skip the other copies of a state we already expanded
            if self.use_graph_search and current_node.state in explored:
                continue

            visiting_order += 1
            current_node.visiting_order = visiting_order

            # goal test when we take the node out of the queue (like UCS)
            if p.is_goal(current_node.state):
                return current_node

            if self.use_graph_search:
                explored.add(current_node.state)

            # expand: apply every action and add the children to the priority queue
            self.nodes_actually_expanded += 1
            for action in p.get_actions():
                next_states = action.apply(current_node.state)
                for s in next_states:
                    # g(n): the real cost from the start
                    path_cost = (current_node.path_cost
                                 + p.get_action_cost(current_node.state, action, s))
                    # f(n) = h(n): Greedy uses only the guess, not the cost
                    f = h.get_h(s)
                    child = Node(s, current_node, action, path_cost, f)
                    heapq.heappush(frontier, child)  # heapq puts it in the right place (by f)
                    self.generated_nodes += 1

        # the queue is empty and we did not find a goal
        return None
