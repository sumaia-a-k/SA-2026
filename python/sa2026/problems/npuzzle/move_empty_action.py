from sa2026.core.i_action import IAction
from sa2026.core.state import State


class MoveEmptyAction(IAction):
    """
    One action of the N-puzzle: move the EMPTY cell up, down, left or right.
    It is the same move as "the tile next to it slides the other way",
    but now there are only 4 actions (not 8 tiles x 4 directions).

    Like MazeAction: one class, and four objects with different directions (see NpuzzleProblem):
      up = MoveEmptyAction("Move empty up", -1, 0)
    (Better than four classes, MoveEmptyUp, ..., with almost the same code.)
    """

    def __init__(self, name: str, row_change: int, col_change: int):
        self._name = name
        self._row_change = row_change  # how much the row of the empty cell changes: -1, 0 or +1
        self._col_change = col_change  # how much the col of the empty cell changes: -1, 0 or +1

    # moves the empty cell one step; returns no state if it would go outside the board
    def apply(self, s: State) -> list[State]:
        new_row = s.get_empty_row() + self._row_change
        new_col = s.get_empty_col() + self._col_change
        n = s.get_size()

        if new_row < 0 or new_row >= n or new_col < 0 or new_col >= n:
            return []  # outside the board: the move is not allowed
        return [s.move_empty_to(new_row, new_col)]

    def get_name(self) -> str:
        return self._name
