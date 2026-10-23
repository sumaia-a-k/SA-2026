from collections import deque  # you need it in TODO 1

from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.core.state import State  # you need it in TODO 1 (for the type hint)


class BFS(SearchAlgorithm):
    """
    STUDENT TASK: write the body of search().
    Everything else is ready. Search for "TODO" and follow the steps.
    Check your work with bfs_demo.py (in this folder).

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

        # TODO 1: create the frontier, a queue of nodes:  frontier: deque[Node] = deque()
        #         create the set of explored states:     explored: set[State] = set()
        #         and a counter:                         visiting_order = 0
        #         Question: why do we create them here, and not as fields of the class?

        # TODO 2: create the start node from p.get_initial_state() and add it to the frontier
        #         (frontier.append(...)). The start node is a generated node too:
        #         self.generated_nodes += 1

        # TODO 3: while the frontier is not empty (while frontier:):
        #   a) take the oldest node out of the queue:  current_node = frontier.popleft()
        #   b) graph search only (self.use_graph_search is True):
        #      if its state is in explored, skip it with "continue".
        #      Question: how can the same state be in the queue two times?
        #   c) visiting_order += 1, then current_node.visiting_order = visiting_order
        #   d) goal test: if p.is_goal(current_node.state), return current_node.
        #      Question: why do we test the goal when we take the node OUT of the queue,
        #                and not when we put it in?
        #   e) graph search only: add the state to explored.
        #   f) expand the node: self.nodes_actually_expanded += 1
        #      then for every action in p.get_actions(),
        #      and for every next state s in action.apply(current_node.state):
        #        - path_cost = current_node.path_cost + p.get_action_cost(current_node.state, action, s)
        #        - child = Node(s, current_node, action, path_cost)
        #        - add the child to the END of the queue, and count it: self.generated_nodes += 1

        # TODO 4: the queue is empty and we did not find a goal: return None.
        return None
