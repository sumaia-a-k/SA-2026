from sa2026.core.heuristic_function import HeuristicFunction
from sa2026.core.state import State
from sa2026.problems.queens.queens_state import QueensState


class DiagonalAttacks(HeuristicFunction):
    """
    h = the number of pairs of queens on the same diagonal.
    The goal has h = 0. Smaller is better, so Hill Climbing goes down to 0.
    """

    def get_h(self, s: State) -> float:
        assert isinstance(s, QueensState)
        return s.count_attacking_pairs()
