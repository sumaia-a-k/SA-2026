from collections import deque

from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.core.state import State


class BFSOptimized(SearchAlgorithm):
    """
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

        frontier: deque[Node] = deque()
        reached: set[State] = set()  # every state we generated: in the queue or expanded
        visiting_order = 0

        start_node = Node(p.get_initial_state())
        frontier.append(start_node)
        self.generated_nodes += 1
        if self.use_graph_search:
            reached.add(start_node.state)

        while frontier:
            current_node = frontier.popleft()
            visiting_order += 1
            current_node.visiting_order = visiting_order

            if p.is_goal(current_node.state):
                return current_node

            self.nodes_actually_expanded += 1
            for action in p.get_actions():
                next_states = action.apply(current_node.state)
                for s in next_states:
                    # the change: we saw this state before, so do not add it again
                    if self.use_graph_search and s in reached:
                        continue
                    if self.use_graph_search:
                        reached.add(s)

                    path_cost = (current_node.path_cost
                                 + p.get_action_cost(current_node.state, action, s))
                    child = Node(s, current_node, action, path_cost)
                    frontier.append(child)
                    self.generated_nodes += 1

        return None
