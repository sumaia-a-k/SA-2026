from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.core.state import State


class DFS(SearchAlgorithm):
    """
    Depth-First Search (DFS), the standard version.

    DFS always goes deeper first. At a dead end it goes back
    to the newest node that is still waiting in the stack.
    The frontier is a stack (LIFO): the last node in is the first node out.

    Tree search:  we do not remember anything. In a graph with cycles
                  DFS can go around a cycle forever!
    Graph search: we remember the explored states and do not expand them again.

    DFS is not optimal: the first path it finds can be a long one.
    """

    # True = graph search, False = tree search (the default)
    def __init__(self, use_graph_search: bool = False):
        super().__init__(use_graph_search)

    def search(self, p: Problem) -> Node | None:
        self._reset_counters()

        # A list is a good stack: append() and pop() both work at the end (the top),
        # and both are fast.
        frontier: list[Node] = []
        explored: set[State] = set()  # set: "in" is fast
        visiting_order = 0

        start_node = Node(p.get_initial_state())
        frontier.append(start_node)
        self.generated_nodes += 1  # the start node is a generated node too

        while frontier:  # while the stack is not empty
            # take the newest node (the top of the stack)
            current_node = frontier.pop()

            # graph search: the same state can be in the stack more than once,
            # so skip it if we expanded it before
            if self.use_graph_search and current_node.state in explored:
                continue

            visiting_order += 1
            current_node.visiting_order = visiting_order

            # goal test when we take the node out of the stack
            if p.is_goal(current_node.state):
                return current_node

            if self.use_graph_search:
                explored.add(current_node.state)

            # expand: apply every action and push the children on the top.
            # The last child we push is the first one we take.
            self.nodes_actually_expanded += 1
            for action in p.get_actions():
                next_states = action.apply(current_node.state)
                for s in next_states:
                    path_cost = (current_node.path_cost
                                 + p.get_action_cost(current_node.state, action, s))
                    child = Node(s, current_node, action, path_cost)
                    frontier.append(child)
                    self.generated_nodes += 1

        # the stack is empty and we did not find a goal
        return None
