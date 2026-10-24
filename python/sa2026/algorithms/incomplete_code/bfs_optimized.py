from collections import deque  # you need it in TODO 1

from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.core.state import State  # you need it in TODO 1 (for the type hint)


class BFSOptimized(SearchAlgorithm):
    """
    STUDENT TASK: write the body of search().
    Do bfs.py first: this class is the same, with one small change.
    Search for "TODO" and follow the steps. Check your work with bfs_demo.py (in this folder).

    BFS with one small change for graph search:
    we check the state when we CREATE the child, not when we take it out of the queue.

    In the standard BFS the same state can go into the queue many times
    (it is skipped later, but it still uses memory).
    Here "reached" has every state we generated: the states in the queue
    and the states already expanded. So each state goes into the queue only once.

    Why "reached" and not "visited"? People use "visited" for two different things
    (added to the queue, or expanded). "reached" is the name in the AIMA book.

    The answer is the same as the standard BFS. We only use less memory and less time.
    In tree search mode this class works exactly like the standard BFS.
    """

    # True = graph search, False = tree search (the default)
    def __init__(self, use_graph_search: bool = False):
        super().__init__(use_graph_search)

    def search(self, p: Problem) -> Node | None:
        self._reset_counters()

        # TODO 1: create the frontier (a deque), the set "reached" (a set of states)
        #         and the counter visiting_order = 0.
        #         "reached" = every state we generated: the states in the queue AND the expanded ones.

        # TODO 2: create the start node, add it to the frontier and count it (self.generated_nodes += 1).
        #         Graph search only: add its state to "reached" too.
        #         Question: what goes wrong if we forget to add the start state here?

        # TODO 3: while the frontier is not empty:
        #   a) take the oldest node out of the queue (popleft).
        #      There is NO "explored" check here. Question: why do we not need it?
        #   b) visiting_order += 1, then current_node.visiting_order = visiting_order
        #   c) goal test: if p.is_goal(current_node.state), return current_node.
        #   d) expand the node: self.nodes_actually_expanded += 1
        #      then for every action and every next state s (like in BFS):
        #        - THE CHANGE: graph search only:
        #            if s is in reached, skip it ("continue"),
        #            else add s to reached
        #        - create the child node with its path_cost (like in BFS),
        #          add it to the end of the queue and count it (self.generated_nodes += 1)

        # TODO 4: the queue is empty and we did not find a goal: return None.
        return None
