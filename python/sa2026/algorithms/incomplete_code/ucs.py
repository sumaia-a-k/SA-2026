import heapq  # you need it in the TODOs

from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.core.state import State  # you need it in TODO 1 (for the type hint)


class UCS(SearchAlgorithm):
    """
    STUDENT TASK: write the body of search().
    Everything else is ready. Search for "TODO" and follow the steps.
    Check your work with ucs_demo.py (in this folder).

    Uniform-Cost Search (UCS).

    UCS always expands the CHEAPEST node first: the node with the smallest
    path cost g(n) (the real cost from the start to the node).
    The frontier is a priority queue: heappop() always gives the node with the smallest cost.

    Tree search:  we do not remember anything, so a state can come back many times.
    Graph search: we remember the explored states and do not expand them again.

    UCS is optimal when every action costs more than 0.
    """

    # True = graph search, False = tree search (the default)
    def __init__(self, use_graph_search: bool = False):
        super().__init__(use_graph_search)

    def search(self, p: Problem) -> Node | None:
        self._reset_counters()

        # The code is almost the same as your bfs.py. Only the frontier is different.

        # TODO 1: create the frontier, a PRIORITY queue of nodes. In Python it is a normal list,
        #         and we use only heapq.heappush() and heapq.heappop() on it:
        #           frontier: list[Node] = []
        #         create the set of explored states:  explored: set[State] = set()
        #         and a counter:                      visiting_order = 0
        #         Question: how does heapq know which node is the cheapest?
        #                   (Look at Node.__lt__() and Node.__init__().)

        # TODO 2: create the start node from p.get_initial_state() and add it to the frontier:
        #           heapq.heappush(frontier, start_node)
        #         Count it: self.generated_nodes += 1
        #         Question: what is the path cost of the start node?

        # TODO 3: while the frontier is not empty (while frontier:):
        #   a) take the CHEAPEST node out of the queue:  current_node = heapq.heappop(frontier)
        #      Question: this is the only line that makes it UCS and not BFS. Why?
        #   b) graph search only: if its state is in explored, skip it with "continue".
        #      Question: the same state can be in the queue two times, with two different costs.
        #                Which copy comes out first?
        #   c) visiting_order += 1, then current_node.visiting_order = visiting_order
        #   d) goal test: if p.is_goal(current_node.state), return current_node.
        #      Question: in BFS it was only "better" to test the goal here.
        #                In UCS it is a MUST. Why? (Hint: S -> G costs 10, S -> A -> G costs 2.)
        #   e) graph search only: add the state to explored.
        #   f) expand the node: self.nodes_actually_expanded += 1
        #      then for every action and every next state s (like in BFS):
        #        - path_cost = current_node.path_cost + p.get_action_cost(current_node.state, action, s)
        #          Be careful: add the cost of THIS action to the cost of the parent.
        #        - child = Node(s, current_node, action, path_cost)
        #        - add the child to the queue:  heapq.heappush(frontier, child)
        #          and count it: self.generated_nodes += 1
        #          heapq puts it in the right place for you (sorted by cost).
        #      Be careful: do not use frontier.append(child). It does not keep the order.

        # TODO 4: the queue is empty and we did not find a goal: return None.
        return None
