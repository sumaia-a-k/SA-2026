from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.core.state import State


class DFSCycleCheck(SearchAlgorithm):
    """
    DFS tree search with a cycle check (also called "path check").

    A cycle is ONE path that comes back to a state that is already on it,
    for example S -> A -> S. Tree search DFS can go around a cycle forever.

    Graph search stops cycles with an explored set, but that set keeps EVERY state
    we expanded (a lot of memory). Here we only look at the path of the node:
    node -> parent -> parent ... -> start. We do not push a child whose state is on it.

    Good:  every cycle is stopped, and we need no new memory (the parents are already there).
    Bad:   the same state can still come again on a DIFFERENT path, so we can do more work.
           And in an INFINITE state space DFS can still go down forever (use DepthLimitedDFS).
    """

    def __init__(self):
        super().__init__(False)  # tree search with a cycle check

    def search(self, p: Problem) -> Node | None:
        self._reset_counters()

        frontier: list[Node] = []
        visiting_order = 0

        start_node = Node(p.get_initial_state())
        frontier.append(start_node)
        self.generated_nodes += 1

        while frontier:
            current_node = frontier.pop()
            visiting_order += 1
            current_node.visiting_order = visiting_order

            if p.is_goal(current_node.state):
                return current_node

            self.nodes_actually_expanded += 1
            for action in p.get_actions():
                next_states = action.apply(current_node.state)
                for s in next_states:
                    # the change: s is already on our path, so it is a cycle
                    if self._is_on_path(current_node, s):
                        continue
                    path_cost = (current_node.path_cost
                                 + p.get_action_cost(current_node.state, action, s))
                    child = Node(s, current_node, action, path_cost)
                    frontier.append(child)
                    self.generated_nodes += 1

        return None

    # True if the state is in this node or in one of its parents
    # @staticmethod: it does not use self (like "static" in Java)
    @staticmethod
    def _is_on_path(node: Node, s: State) -> bool:
        n = node
        while n is not None:
            if n.state == s:
                return True
            n = n.parent
        return False
