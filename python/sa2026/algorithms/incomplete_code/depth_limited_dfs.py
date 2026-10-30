from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.core.state import State


class DepthLimitedDFS(SearchAlgorithm):
    """
    STUDENT TASK: write the body of search() and the body of _is_on_path().
    Do dfs_cycle_check.py first: this class is the same, with a depth limit.
    Search for "TODO" and follow the steps. Check your work with dfs_demo.py (in this folder).

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
        self._limit = limit      # do not expand nodes at this depth
        self._cutoff = False     # only a flag: did at least one node stop at the limit? (yes / no)

    # IDS asks this after the search: True = try a bigger limit, False = no solution
    def is_cutoff(self) -> bool:
        return self._cutoff

    def search(self, p: Problem) -> Node | None:
        self._reset_counters()

        # TODO 1: a new search: no cutoff yet, so set self._cutoff = False.
        #         Question: what goes wrong if the same object is used two times and we forget this?

        # TODO 2: create the frontier (a stack) and visiting_order = 0.
        #         Create the start node, push it and count it (self.generated_nodes += 1).

        # TODO 3: while the frontier is not empty:
        #   a) pop the newest node, and set its visiting order.
        #   b) goal test: if p.is_goal(current_node.state), return current_node.
        #   c) THE CHANGE: if current_node.depth >= self._limit:
        #        set self._cutoff = True, and do not expand the node ("continue").
        #      Question: why is the goal test BEFORE this test, and not after it?
        #   d) expand the node: self.nodes_actually_expanded += 1
        #      then for every action and every next state s (like in dfs_cycle_check.py):
        #        - if self._is_on_path(current_node, s), skip s ("continue")
        #        - create the child node with its path_cost, push it and count it.

        # TODO 4: the stack is empty and we did not find a goal: return None.
        return None

    # True if the state is in this node or in one of its parents
    def _is_on_path(self, node: Node, s: State) -> bool:
        # TODO 5: the same as _is_on_path() in your dfs_cycle_check.py
        return False
