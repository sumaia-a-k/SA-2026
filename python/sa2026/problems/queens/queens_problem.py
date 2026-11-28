from random import Random

from sa2026.core.heuristic_function import HeuristicFunction
from sa2026.core.i_action import IAction
from sa2026.core.problem import Problem
from sa2026.core.state import State
from sa2026.problems.queens.diagonal_attacks import DiagonalAttacks
from sa2026.problems.queens.queens_state import QueensState
from sa2026.problems.queens.swap_queens_action import SwapQueensAction


class QueensProblem(Problem):
    """
    The 8-queens problem: put 8 queens on a chess board so that no two attack each other.
    (A queen attacks along its row, its column and its two diagonals.)

    Initial state: a board with one queen in every row and every column (see QueensState).
    Goal:          no two queens on the same diagonal (h = 0).
    Actions:       swap two queens (28 neighbours).
    Cost:          every swap costs 1. (We do not care about the path, only about the final board.)
    Heuristic:     DiagonalAttacks: the number of pairs of queens on the same diagonal.

    This problem is for local search (Hill Climbing). It can also make a random start state
    (get_random_state), so RandomRestart can use it.
    """

    # "*rows": give the row of the queen of each column, for example
    #   QueensProblem(0, 1, 3, 4, 5, 2, 7, 6)
    # Every row from 0 to n-1 must be used once (one queen in every row).
    def __init__(self, *rows: int):
        QueensProblem._check(rows)
        self._initial_state = QueensState(rows)
        self._actions: list[IAction] = [SwapQueensAction()]
        self._heuristic: HeuristicFunction = DiagonalAttacks()

    # Example 1 of the lesson page: h = 9, Hill Climbing solves it in 3 swaps
    @staticmethod
    def example1() -> "QueensProblem":
        return QueensProblem(0, 1, 3, 4, 5, 2, 7, 6)

    # Example 2 of the lesson page: h = 9, Hill Climbing gets stuck at h = 1 (a flat place)
    @staticmethod
    def example2() -> "QueensProblem":
        return QueensProblem(0, 1, 2, 5, 6, 7, 4, 3)

    # checks the board and raises an error with a clear message if it is wrong
    @staticmethod
    def _check(rows) -> None:
        if len(rows) < 1:
            raise ValueError("The board needs at least one queen.")
        if sorted(rows) != list(range(len(rows))):
            raise ValueError(f"Each row from 0 to {len(rows) - 1} must have exactly one queen.")

    def get_initial_state(self) -> State:
        return self._initial_state

    def is_goal(self, state: State) -> bool:
        return state.is_goal()

    def get_actions(self) -> list[IAction]:
        return self._actions

    # every swap costs the same
    def get_action_cost(self, s: State, a: IAction, next_state: State) -> float:
        return 1

    def get_heuristic_function(self) -> HeuristicFunction:
        return self._heuristic

    # a random board of the same size: the rows 0, 1, ..., n-1 in a random order
    def get_random_state(self, random: Random) -> State:
        rows = list(range(self._initial_state.get_size()))
        # mix the rows, like shuffling cards
        random.shuffle(rows)
        return QueensState(rows)
