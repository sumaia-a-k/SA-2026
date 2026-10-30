from collections import deque

from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.core.state import State


class BFS(SearchAlgorithm):
    """
    Breadth-First Search (BFS), the standard version.

    BFS visits the nodes level by level: first depth 0, then depth 1, then depth 2 ...
    The frontier is a queue (FIFO): the first node in is the first node out.

    Tree search:  we do not remember anything, so a state can come back many times.
    Graph search: we remember the explored states and do not expand them again.

    BFS is optimal only when all the actions have the same cost.
    """

    # True = graph search, False = tree search (the default)
    def __init__(self, use_graph_search: bool = False):
        super().__init__(use_graph_search)

    def search(self, p: Problem) -> Node | None:
        self._reset_counters()

        # We create these here and not as fields,
        # so every new search starts with an empty queue.
        # deque = a queue that is fast at both ends. A normal list is slow
        # with pop(0), because it moves all the other items one place.
        frontier: deque[Node] = deque()
        explored: set[State] = set()  # set: "in" is fast
        visiting_order = 0

        start_node = Node(p.get_initial_state())
        frontier.append(start_node)
        self.generated_nodes += 1  # the start node is a generated node too

        while frontier:  # while the queue is not empty
            # take the oldest node (the first one in the queue)
            current_node = frontier.popleft()

            # graph search: the same state can be in the queue more than once,
            # so skip it if we expanded it before
            if self.use_graph_search and current_node.state in explored:
                continue

            visiting_order += 1
            current_node.visiting_order = visiting_order

            # goal test when we take the node out of the queue
            if p.is_goal(current_node.state):
                return current_node

            if self.use_graph_search:
                explored.add(current_node.state)

            # expand: apply every action and add the children to the end of the queue
            self.nodes_actually_expanded += 1
            for action in p.get_actions():
                next_states = action.apply(current_node.state)
                for s in next_states:
                    path_cost = (current_node.path_cost
                                 + p.get_action_cost(current_node.state, action, s))
                    child = Node(s, current_node, action, path_cost)
                    frontier.append(child)
                    self.generated_nodes += 1

        # the queue is empty and we did not find a goal
        return None
