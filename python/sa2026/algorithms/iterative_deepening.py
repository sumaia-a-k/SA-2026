from sa2026.algorithms.depth_limited_dfs import DepthLimitedDFS
from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm


class IterativeDeepening(SearchAlgorithm):
    """
    Iterative Deepening Search (IDS).

    We do not know the depth of the goal, so we try every limit:
    DepthLimitedDFS with limit 0, then 1, then 2, ... until we find the goal.

    The first limit that finds a goal is its depth, so the path is a shortest one
    (the same answer as BFS, if all steps cost the same).
    But the memory is small, like DFS: only one path and the nodes that wait next to it.

    If the state space is INFINITE and there is no solution, IDS never stops (BFS neither).
    """

    def __init__(self):
        super().__init__(False)  # every iteration is a tree search with a cycle check

    def search(self, p: Problem) -> Node | None:
        self._reset_counters()

        # try limit 0, 1, 2, ... until we find the goal
        limit = 0
        while True:
            dls = DepthLimitedDFS(limit)
            result = dls.search(p)

            # count the work of every iteration
            self.generated_nodes += dls.generated_nodes
            self.nodes_actually_expanded += dls.nodes_actually_expanded

            if result is not None:
                return result  # found the goal
            if not dls.is_cutoff():
                return None    # no node stopped at the limit: there is no solution
            limit += 1
