from abc import ABC, abstractmethod

from sa2026.core.node import Node
from sa2026.core.problem import Problem


class SearchAlgorithm(ABC):
    """
    The parent class of all search algorithms (BFS, DFS, UCS, A*, ...).
    Each algorithm writes its own search() method.
    """

    # use_graph_search:
    #   False = tree search (a state can be visited again). This is the default.
    #   True  = graph search (we remember explored states and do not visit them again)
    # The child algorithm passes its mode here, for example: super().__init__(use_graph_search)
    def __init__(self, use_graph_search: bool = False):
        self.use_graph_search = use_graph_search

        # number of child nodes created (generated)
        self.developed_nodes = 0

        # number of nodes taken from the frontier and expanded
        self.nodes_actually_expanded = 0

    # Searches for a goal and returns the goal node, or None if there is no solution.
    # Call _reset_counters() at the start, so the numbers are correct
    # when the same algorithm object is used more than once.
    @abstractmethod
    def search(self, p: Problem) -> Node | None:
        pass

    # Sets the counters back to 0.
    # The "_" at the start of the name means: use it only in this class and its children
    # (like "protected" in Java). Python does not stop you, it is only a rule between programmers.
    def _reset_counters(self):
        self.developed_nodes = 0
        self.nodes_actually_expanded = 0

    # prints every step from the start to the goal
    def print_solution(self, solution: Node | None):
        if solution is None:
            print("No solution found.")
            return
        for node in solution.get_path_from_root():
            print(node)
        print(f"Solution cost: {solution.path_cost}")
        print(f"Solution steps: {solution.depth}")
        print(f"Developed nodes: {self.developed_nodes}")
        print(f"Expanded nodes: {self.nodes_actually_expanded}")
