from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.core.state import State


class BeamSearch(SearchAlgorithm):
    """
    Beam Search.

    Beam Search is Greedy with a small frontier. The frontier can keep only
    k nodes (k = the beam width). After each expansion we sort the WHOLE frontier
    (old nodes and new children together) by f(n) = h(n), keep the k best nodes
    and throw away the rest. A node that we throw away never comes back.

    The code is the same as Greedy. Only two things are different:
      1. the frontier is a normal list, not a heapq, because we must cut it
      2. one new step after each expansion: keep only the k best nodes
    Same h: the node that came into the frontier first stays first (the sort keeps the order).

    k = 1:         only one node in the frontier. It always goes to the best child (close to Hill Climbing).
    k = no limit:  nothing is thrown away. It is Greedy (only nodes with the same h
                   can come out in another order: heapq does not keep the order).

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

        # the guess h(n) of this problem (raises an error if the problem has no heuristic)
        h = p.get_heuristic_function()

        # the frontier is a list, sorted by f(n): the best node is the first one (index 0)
        frontier: list[Node] = []
        explored: set[State] = set()  # set: "in" is fast
        visiting_order = 0

        # the start node: path cost 0, f(n) = h(n)
        start = p.get_initial_state()
        start_node = Node(start, None, None, 0.0, h.get_h(start))
        frontier.append(start_node)
        self.generated_nodes += 1  # the start node is a generated node too

        while frontier:  # while the frontier is not empty
            # take the node with the smallest f(n): the first one in the list
            current_node = frontier.pop(0)

            # graph search: skip the other copies of a state we already expanded
            if self.use_graph_search and current_node.state in explored:
                continue

            visiting_order += 1
            current_node.visiting_order = visiting_order

            # goal test when we take the node out of the frontier (like Greedy)
            if p.is_goal(current_node.state):
                return current_node

            if self.use_graph_search:
                explored.add(current_node.state)

            # expand: apply every action and add the children to the end of the list
            self.nodes_actually_expanded += 1
            for action in p.get_actions():
                next_states = action.apply(current_node.state)
                for s in next_states:
                    # g(n): the real cost from the start (only to know the cost of the path)
                    path_cost = (current_node.path_cost
                                 + p.get_action_cost(current_node.state, action, s))
                    # f(n) = h(n), like Greedy
                    f = h.get_h(s)
                    child = Node(s, current_node, action, path_cost, f)
                    frontier.append(child)
                    self.generated_nodes += 1

            # sort the whole frontier by f(n) (Node.__lt__()).
            # sort() keeps the order of two nodes with the same f(n), so the older one stays first.
            frontier.sort()

            # NEW in Beam Search: keep only the k best nodes, throw away the rest
            while len(frontier) > self.beam_width:
                frontier.pop()  # the worst node is the last one
                self.thrown_away_nodes += 1

        # the frontier is empty and we did not find a goal
        # (maybe there is a goal, but we threw its way away)
        return None
