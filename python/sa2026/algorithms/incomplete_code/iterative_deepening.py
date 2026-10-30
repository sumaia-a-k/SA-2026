from sa2026.algorithms.incomplete_code.depth_limited_dfs import DepthLimitedDFS  # your DLS
from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm


class IterativeDeepening(SearchAlgorithm):
    """
    STUDENT TASK: write the body of search().
    Do depth_limited_dfs.py first: IDS only calls it again and again.
    Search for "TODO" and follow the steps. Check your work with dfs_demo.py (in this folder).

    Iterative Deepening Search (IDS).

    We do not know the depth of the goal, so we try every limit:
    DepthLimitedDFS with limit 0, then 1, then 2, ... until we find the goal.

    The first limit that finds a goal is its depth, so the path is a shortest one
    (the same answer as BFS, if all steps cost the same).
    But the memory is small, like DFS: only one path and the nodes that wait next to it.
    """

    def __init__(self):
        super().__init__(False)  # every iteration is a tree search with a cycle check

    def search(self, p: Problem) -> Node | None:
        self._reset_counters()

        # TODO 1: start with limit = 0 and write a loop that never stops by itself: while True:
        #   a) create a DepthLimitedDFS with this limit (your class, in this folder),
        #      and run it:  result = dls.search(p)
        #   b) add its counters to ours, so we count the work of EVERY iteration:
        #        self.generated_nodes += dls.generated_nodes
        #        self.nodes_actually_expanded += dls.nodes_actually_expanded
        #   c) if result is not None, we found the goal: return result.
        #   d) if dls.is_cutoff() is False, no node stopped at the limit.
        #      We searched everything, so there is no solution: return None.
        #      Question: what happens if we forget this test and there is no solution?
        #   e) limit += 1
        return None
