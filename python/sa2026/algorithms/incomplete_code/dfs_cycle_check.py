from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.core.state import State


class DFSCycleCheck(SearchAlgorithm):
    """
    STUDENT TASK: write the body of search() and the body of _is_on_path().
    Do dfs.py first: this class is DFS tree search with one small change.
    Search for "TODO" and follow the steps. Check your work with dfs_demo.py (in this folder).

    DFS tree search with a cycle check (also called "path check").

    A cycle is ONE path that comes back to a state that is already on it,
    for example S -> A -> S. Tree search DFS can go around a cycle forever.

    Graph search stops cycles with an explored set, but that set keeps EVERY state
    we expanded (a lot of memory). Here we only look at the path of the node:
    node -> parent -> parent ... -> start. We do not push a child whose state is on it.

    Good:  every cycle is stopped, and we need no new memory (the parents are already there).
    Bad:   the same state can still come again on a DIFFERENT path, so we can do more work.
    """

    def __init__(self):
        super().__init__(False)  # tree search with a cycle check

    def search(self, p: Problem) -> Node | None:
        self._reset_counters()

        # TODO 1: create the frontier (a stack: a list) and visiting_order = 0.
        #         There is NO explored set here. Question: why not?

        # TODO 2: create the start node, push it and count it (self.generated_nodes += 1).

        # TODO 3: while the frontier is not empty:
        #   a) pop the newest node, and set its visiting order.
        #   b) goal test: if p.is_goal(current_node.state), return current_node.
        #   c) expand the node: self.nodes_actually_expanded += 1
        #      then for every action and every next state s (like in DFS):
        #        - THE CHANGE: if self._is_on_path(current_node, s) is True, skip s ("continue").
        #          It would make a cycle.
        #        - create the child node with its path_cost, push it and count it.

        # TODO 4: the stack is empty and we did not find a goal: return None.
        return None

    # True if the state is in this node or in one of its parents
    def _is_on_path(self, node: Node, s: State) -> bool:
        # TODO 5: start with n = node. While n is not None:
        #           - if n.state == s, return True
        #           - go up one step: n = n.parent
        #         At the end (we reached above the start node): return False.
        #         Question: "==" calls __eq__() of the state. Why is "is" not good here?
        return False
