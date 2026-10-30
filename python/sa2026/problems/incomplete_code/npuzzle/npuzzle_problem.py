import math

from sa2026.core.i_action import IAction
from sa2026.core.problem import Problem
from sa2026.core.state import State
from sa2026.problems.incomplete_code.npuzzle.move_empty_action import MoveEmptyAction  # you need it in TODO 2
from sa2026.problems.incomplete_code.npuzzle.npuzzle_state import NpuzzleState  # you need it in TODO 1


class NpuzzleProblem(Problem):
    """
    STUDENT TASK: finish this class.

    The N-puzzle problem (8-puzzle, 15-puzzle, ...): slide the tiles until they are in order.

    Initial state: the board we get (0 = the empty cell).
    Goal:          1, 2, 3, ..., n*n-1 and the empty cell at the end.
    Actions:       move the empty cell up, down, left, right.
    Cost:          every move costs 1.

    There is no heuristic yet. We add it in a later session.

    Search for "TODO" and follow the steps.
    """

    # "*tiles": give the tiles row by row, for example  NpuzzleProblem(4, 1, 2, 5, 8, 3, 7, 6, 0)
    # (like "int..." in Java). Raises a ValueError if the board is wrong or can not be solved.
    def __init__(self, *tiles: int):
        NpuzzleProblem._check(tiles)

        # TODO 1: create the initial state from the tiles. Hint: NpuzzleState(tiles)
        self._initial_state = None

        # TODO 2: make the list self._actions with the four actions.
        #         Use these names and changes of the EMPTY cell (row_change, col_change):
        #           "Move empty up"    (-1,  0)
        #           "Move empty down"  ( 1,  0)
        #           "Move empty left"  ( 0, -1)
        #           "Move empty right" ( 0,  1)
        #         The order of this list is the order the algorithms try the actions.
        self._actions: list[IAction] = []

    # the three tests from the 2025 code
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
        # TODO 7 (a bit harder): count the inversions.
        #   For every i, and every j > i: if tiles[i] and tiles[j] are not 0
        #   and tiles[i] > tiles[j], it is one inversion.
        #   Then use the rules above. n = math.isqrt(len(tiles))
        #   Check: [1, 2, 3, 4, 5, 6, 8, 7, 0] has 1 inversion, so it can NOT be solved.
        #   Question: why does a move left or right never change the number of inversions?
        return True

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
        # TODO 3: return the initial state.
        return None

    def is_goal(self, state: State) -> bool:
        # TODO 4: ask the state if it is a goal.
        return False

    def get_actions(self) -> list[IAction]:
        # TODO 5: return the list of actions.
        return None

    # The cost of going from state s to state next_state using action a.
    def get_action_cost(self, s: State, a: IAction, next_state: State) -> float:
        # TODO 6: every move costs the same. Return 1.
        return 0
