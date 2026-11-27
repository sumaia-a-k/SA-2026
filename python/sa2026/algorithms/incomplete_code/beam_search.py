from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.core.state import State  # you need it in TODO 1 (for the type hint)


class BeamSearch(SearchAlgorithm):
    """
    STUDENT TASK: write the body of search().
    Everything else is ready. Search for "TODO" and follow the steps.
    Check your work with beam_demo.py (in this folder).

    Beam Search.

    Beam Search is Greedy with a small frontier. The frontier can keep only
    k nodes (k = the beam width). After each expansion we sort the WHOLE frontier
    (old nodes and new children together) by f(n) = h(n), keep the k best nodes
    and throw away the rest. A node that we throw away never comes back.

    Tree search and graph search: NOT complete. The way to the goal can be thrown away.
    Beam Search is NOT optimal. Its good point: the frontier has at most k nodes after each step.
    """

    # beam_width = k: the most nodes the frontier can keep
    # True = graph search, False = tree search (the default)
    def __init__(self, beam_width: int, use_graph_search: bool = False):
        super().__init__(use_graph_search)
        if beam_width < 1:
            raise ValueError(f"The beam width k must be 1 or more, not {beam_width}.")
        self.beam_width = beam_width
        self.thrown_away_nodes = 0  # how many nodes the last search threw away

    def search(self, p: Problem) -> Node | None:
        self._reset_counters()
        self.thrown_away_nodes = 0  # a new search: nothing thrown away yet

        # The code is almost the same as your greedy.py. Only the frontier and one new step are different.

        # TODO 1: like in Greedy: h = p.get_heuristic_function(),
        #         explored: set[State] = set()  and  visiting_order = 0
        #         NEW: the frontier is a normal list, and we do NOT use heapq:
        #           frontier: list[Node] = []
        #         Question: why can we not use heapq here? (Look at TODO 3 h.)

        # TODO 2: like in Greedy: create the start node with FIVE values:
        #           Node(start, None, None, 0.0, h.get_h(start))
        #         (start = p.get_initial_state()). Add it with frontier.append(...)
        #         and count it: self.generated_nodes += 1

        # TODO 3: while the frontier is not empty (while frontier:):
        #   a) take the best node. The list is sorted, so the best node is the first one:
        #        current_node = frontier.pop(0)
        #   b) graph search only: if its state is in explored, skip it with "continue".
        #   c) visiting_order += 1  and  current_node.visiting_order = visiting_order
        #   d) goal test: if p.is_goal(current_node.state), return current_node.
        #   e) graph search only: add the state to explored.
        #   f) expand the node, like in Greedy: self.nodes_actually_expanded += 1
        #      then for every action and every next state s:
        #        - path_cost = current_node.path_cost + p.get_action_cost(current_node.state, action, s)
        #        - f = h.get_h(s)
        #        - child = Node(s, current_node, action, path_cost, f)
        #        - frontier.append(child)  (at the end of the list for now)  and count it: self.generated_nodes += 1
        #   g) after the for loops: sort the WHOLE frontier by f(n):  frontier.sort()
        #      Question: two nodes have the same h. Which one is first after the sort?
        #                (sort() does not change the order of equal nodes.)
        #   h) NEW in Beam Search: keep only the k best nodes. While len(frontier) > self.beam_width:
        #        - remove the last node (the worst one):  frontier.pop()
        #        - count it: self.thrown_away_nodes += 1
        #      Question: can a node that was in the frontier BEFORE this step be thrown away too?
        #                (Look at step 3 of the trace on beam.html.)
        #   Question: run beam_demo.py. With the misleading guess and k = 1 your search returns None,
        #             but the path S -> B -> E -> G exists. Why?

        # TODO 4: the frontier is empty and we did not find a goal: return None.
        return None
