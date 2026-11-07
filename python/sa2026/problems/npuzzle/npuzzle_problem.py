import math

from sa2026.core.i_action import IAction
from sa2026.core.problem import Problem
from sa2026.core.state import State
from sa2026.problems.npuzzle.move_empty_action import MoveEmptyAction
from sa2026.problems.npuzzle.npuzzle_state import NpuzzleState


class NpuzzleProblem(Problem):
    """
    The N-puzzle problem (8-puzzle, 15-puzzle, ...): slide the tiles until they are in order.

    Initial state: the board we get (0 = the empty cell).
    Goal:          1, 2, 3, ..., n*n-1 and the empty cell at the end.
    Actions:       move the empty cell up, down, left, right.
    Cost:          every move costs 1.

    There is no heuristic yet. We add it in a later session (for example the Hamming distance).

    Checks on the start board:
     - The start board is checked: it must be n x n, have every number 0 .. n*n-1 once,
       and it must be solvable. (A random shuffle makes a board with NO solution half of the time,
       and then the search looks at every reachable state before it says "no solution".)
    """

    # "*tiles": give the tiles row by row, for example  NpuzzleProblem(4, 1, 2, 5, 8, 3, 7, 6, 0)
    # (like "int..." in Java). Raises a ValueError if the board is wrong or can not be solved.
    def __init__(self, *tiles: int):
        NpuzzleProblem._check(tiles)
        self._initial_state = NpuzzleState(tiles)

        # the order of this list is the order the algorithms try the actions
        self._actions: list[IAction] = [
            MoveEmptyAction("Move empty up", -1, 0),
            MoveEmptyAction("Move empty down", 1, 0),
            MoveEmptyAction("Move empty left", 0, -1),
            MoveEmptyAction("Move empty right", 0, 1),
        ]

    # the three tests: easy, medium, hard
    @staticmethod
    def easy() -> "NpuzzleProblem":
        return NpuzzleProblem(1, 2, 3, 4, 0, 5, 7, 8, 6)   # 2 moves

    @staticmethod
    def medium() -> "NpuzzleProblem":
        return NpuzzleProblem(4, 1, 2, 5, 8, 3, 7, 6, 0)   # 8 moves

    @staticmethod
    def hard() -> "NpuzzleProblem":
        return NpuzzleProblem(1, 8, 3, 2, 6, 4, 7, 0, 5)   # 19 moves

    # Can this board reach the goal? Only HALF of all boards can.
    # Read the tiles row by row, skip the 0, and count the "inversions":
    # the pairs where a bigger number comes before a smaller one.
    #   n odd  (3 x 3): solvable if the number of inversions is even.
    #   n even (4 x 4): solvable if inversions + (the row of the empty cell,
    #                   counted from the bottom: 1, 2, 3, ...) is odd.
    @staticmethod
    def is_solvable(tiles) -> bool:
        n = math.isqrt(len(tiles))
        inversions = 0
        empty_index = 0
        for i in range(len(tiles)):
            if tiles[i] == 0:
                empty_index = i
                continue
            for j in range(i + 1, len(tiles)):
                if tiles[j] != 0 and tiles[i] > tiles[j]:
                    inversions += 1
        if n % 2 == 1:
            return inversions % 2 == 0
        empty_row_from_bottom = n - empty_index // n
        return (inversions + empty_row_from_bottom) % 2 == 1

    # checks the start board and raises an error with a clear message if it is wrong
    @staticmethod
    def _check(tiles):
        n = math.isqrt(len(tiles))
        if n < 2 or n * n != len(tiles):
            raise ValueError(f"The board must be n x n (4, 9, 16, ... numbers), not {len(tiles)} numbers.")
        if sorted(tiles) != list(range(len(tiles))):
            raise ValueError(f"Each number from 0 to {len(tiles) - 1} must be on the board once.")
        if not NpuzzleProblem.is_solvable(tiles):
            raise ValueError("This board can never be solved (see is_solvable()).")

    def get_initial_state(self) -> State:
        return self._initial_state

    def is_goal(self, state: State) -> bool:
        return state.is_goal()

    def get_actions(self) -> list[IAction]:
        return self._actions

    # every move costs the same
    def get_action_cost(self, s: State, a: IAction, next_state: State) -> float:
        return 1
