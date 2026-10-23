from sa2026.core.i_action import IAction
from sa2026.core.state import State
from sa2026.problems.maze.maze_state import MazeState


class MazeAction(IAction):
    """
    One move of the player: up, down, left or right.

    All four moves work the same way, only the direction is different.
    So we use one class and give it the direction (row_change, col_change).
    From this one class we create four action objects (see MazeProblem):
      move_up    = MazeAction("Move up",    -1,  0)
      move_down  = MazeAction("Move down",   1,  0)
      move_left  = MazeAction("Move left",   0, -1)
      move_right = MazeAction("Move right",  0,  1)
    """

    def __init__(self, name: str, row_change: int, col_change: int):
        self._name = name
        self._row_change = row_change  # how much the row changes: -1, 0 or +1
        self._col_change = col_change  # how much the column changes: -1, 0 or +1

    # moves the player one cell; returns no state if the new cell is a wall or outside
    def apply(self, s: State) -> list[State]:
        # Java needs a cast here: (MazeState) s. Python does not, we just use s.row and s.col.
        # MazeProblem only creates MazeState objects. If another state comes here, it is a bug,
        # and the AttributeError ("has no attribute 'row'") shows it fast.
        new_row = s.row + self._row_change
        new_col = s.col + self._col_change

        if not MazeState.maze.is_free(new_row, new_col):
            return []  # the move is not allowed
        next_state = MazeState(new_row, new_col)

        # The result is a list because in other problems one action can give many states.
        return [next_state]

    def get_name(self) -> str:
        return self._name
