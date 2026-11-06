from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.core.state import State


class DepthLimitedDFS(SearchAlgorithm):
    """
    Depth-Limited Search (DLS): DFS with a cycle check and a depth limit.

    A node at depth = limit is NOT expanded. So DFS can not go down forever.

    limit < depth of the goal:  no goal is found (returns None).
    limit = depth of the goal:  a shortest path is found (if all steps cost the same).
    limit > depth of the goal:  a goal is found, but maybe a long path.

    When it returns None, is_cutoff() tells us why:
      True  = a node stopped at the limit: maybe there is a goal deeper.
      False = we searched everything: there is no goal at all.
    """

    def __init__(self, limit: int):
        super().__init__(False)  # tree search with a cycle check
        if limit < 0:
            raise ValueError(f"The limit must be 0 or more, not {limit}.")
        self._limit = limit      # do not expand nodes at this depth
        self._cutoff = False     # only a flag: did at least one node stop at the limit? (yes / no)

    # IDS asks this after the search: True = try a bigger limit, False = no solution
    def is_cutoff(self) -> bool:
        return self._cutoff

    def search(self, p: Problem) -> Node | None:
        self._reset_counters()
        self._cutoff = False  # a new search: no cutoff yet

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

            # do not go deeper than the limit
            if current_node.depth >= self._limit:
                self._cutoff = True  # remember that it happened, nothing more
                continue

            self.nodes_actually_expanded += 1
            for action in p.get_actions():
                next_states = action.apply(current_node.state)
                for s in next_states:
                    # cycle check: do not go back to a state on our own path
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
