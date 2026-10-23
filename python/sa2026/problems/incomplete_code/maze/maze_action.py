from sa2026.core.i_action import IAction
from sa2026.core.state import State
from sa2026.problems.incomplete_code.maze.maze_state import MazeState  # you need it in TODO 5


class MazeAction(IAction):
    """
    STUDENT TASK: finish this class.

    One move of the player: up, down, left or right.
    All four moves work the same way, only the direction is different.
    So we use ONE class and give it the direction (row_change, col_change).
    From this one class we create four action objects (in MazeProblem), for example:
      move_up = MazeAction("Move up", -1, 0)

    Search for "TODO" and follow the steps.
    """

    # TODO 1 and 2: write the constructor __init__(self, name, row_change, col_change).
    #         In Python the fields are made inside the constructor, so this one step does both:
    #         save the three values in self._name, self._row_change, self._col_change
    #         row_change and col_change are -1, 0 or +1.
    #         Example: "Move up" -> row_change = -1, col_change = 0

    # Moves the player one cell. Returns no state if the new cell is a wall or outside.
    def apply(self, s: State) -> list[State]:
        # TODO 3: Java needs a cast here. Python does not: s is a MazeState,
        #         so you can use s.row and s.col directly.
        #         Question: what happens if someone passes another kind of state?
        # TODO 4: find the new row and the new col (current position + the changes).
        # TODO 5: ask the maze if the new cell is free. Hint: MazeState.maze.is_free(...)
        #         - if NOT free: return []
        #         - if free:     create a new MazeState for the new cell
        #                        and return [new_state]
        #
        # Important: do NOT change the old state. Always create a new one.
        return []

    def get_name(self) -> str:
        # TODO 6: return the name.
        return None
