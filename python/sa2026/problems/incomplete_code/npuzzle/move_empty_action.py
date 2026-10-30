from sa2026.core.i_action import IAction
from sa2026.core.state import State


class MoveEmptyAction(IAction):
    """
    STUDENT TASK: finish this class.

    One action of the N-puzzle: move the EMPTY cell up, down, left or right.
    It is the same move as "the tile next to it slides the other way",
    but now there are only 4 actions (not 8 tiles x 4 directions).

    Like MazeAction: one class, and four objects with different directions (see NpuzzleProblem):
      up = MoveEmptyAction("Move empty up", -1, 0)

    Search for "TODO" and follow the steps.
    """

    # TODO 1 and 2: write the constructor __init__(self, name, row_change, col_change).
    #               Save the three values: self._name, self._row_change, self._col_change
    #               They are the change of the EMPTY cell: -1, 0 or +1.

    # Moves the empty cell one step. Returns no state if it would go outside the board.
    def apply(self, s: State) -> list[State]:
        # TODO 3: (Python needs no cast, s is an NpuzzleState.)
        # TODO 4: find the new row and col of the empty cell:
        #         s.get_empty_row() + self._row_change, s.get_empty_col() + self._col_change
        # TODO 5: n = s.get_size(). If the new row or col is outside 0 .. n-1: return []
        #         Else: return [s.move_empty_to(new_row, new_col)]
        #         Question: why is there no wall check here, like in the maze?
        return []

    def get_name(self) -> str:
        # TODO 6: return the name.
        return ""
