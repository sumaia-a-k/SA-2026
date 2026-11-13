import heapq

from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.core.state import State


class UCS(SearchAlgorithm):
    """
    Uniform-Cost Search (UCS).

    UCS always expands the CHEAPEST node first: the node with the smallest
    path cost g(n) (the real cost from the start to the node).
    The frontier is a priority queue: heappop() always gives the node with the smallest cost.

    The code is the same as BFS. Only the frontier is different:
      BFS: a queue (deque)       -> takes the OLDEST node    (fewest steps)
      UCS: a priority queue      -> takes the CHEAPEST node  (smallest cost)

    Tree search:  we do not remember anything, so a state can come back many times.
    Graph search: we remember the explored states and do not expand them again.

    UCS is optimal when every action costs more than 0.
    If all the actions cost the same, UCS expands the nodes like BFS.
    """

    # True = graph search, False = tree search (the default)
    def __init__(self, use_graph_search: bool = False):
        super().__init__(use_graph_search)

    def search(self, p: Problem) -> Node | None:
        self._reset_counters()

        # Python has no PriorityQueue class for this. We use a normal list
        # and the heapq functions: heappush() and heappop() keep the cheapest node first.
        # heapq uses Node.__lt__(): the node with the smallest total_cost comes first.
        # For UCS, total_cost = path_cost = g(n) (see Node.__init__).
        frontier: list[Node] = []
        explored: set[State] = set()  # set: "in" is fast
        visiting_order = 0

        start_node = Node(p.get_initial_state())
        heapq.heappush(frontier, start_node)
        self.generated_nodes += 1  # the start node is a generated node too

        while frontier:  # while the queue is not empty
            # take the cheapest node (the smallest path cost)
            current_node = heapq.heappop(frontier)

            # graph search: the same state can be in the queue more than once
            # (with different costs). The cheapest copy comes out first,
            # so skip the other copies if we expanded this state before.
            if self.use_graph_search and current_node.state in explored:
                continue

            visiting_order += 1
            current_node.visiting_order = visiting_order

            # goal test when we take the node out of the queue.
            # In UCS this is VERY important: a goal we only generated
            # may still have a cheaper path that we did not find yet.
            if p.is_goal(current_node.state):
                return current_node

            if self.use_graph_search:
                explored.add(current_node.state)

            # expand: apply every action and add the children to the priority queue
            self.nodes_actually_expanded += 1
            for action in p.get_actions():
                next_states = action.apply(current_node.state)
                for s in next_states:
                    path_cost = (current_node.path_cost
                                 + p.get_action_cost(current_node.state, action, s))
                    child = Node(s, current_node, action, path_cost)
                    heapq.heappush(frontier, child)  # heapq puts it in the right place (by cost)
                    self.generated_nodes += 1

        # the queue is empty and we did not find a goal
        return None
