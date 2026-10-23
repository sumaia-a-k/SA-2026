from sa2026.core.state import State
from sa2026.problems.incomplete_code.maze.maze import Maze


class MazeState(State):
    """
    STUDENT TASK: finish this class.

    A state of the maze problem = where the player is now (row, col).
    Only row and col are the state.

    Search for "TODO" and follow the steps.
    """

    # The maze is NOT part of the state. The walls and the goal never change.
    # We keep it here only to check the goal and to draw the state.
    #
    # It is a class variable: it is written here, not in __init__.
    # So there is ONE maze for all states, not one per state (like "static" in Java).
    # It takes no extra memory per state. It is not used in __eq__; __hash__ only reads its number of columns.
    # Limit: we can work with only one maze at a time. A new maze replaces the old one.
    #
    # Change it with  MazeState.maze = ...   and NOT with  self.maze = ...
    # (self.maze = ... makes a new variable inside that one object only).
    #
    # Other options:
    #  1. A normal variable (self.maze in __init__): each state keeps a reference to the same maze.
    #     It costs only one reference per state, and we can have many mazes.
    #  2. Keep the maze only in MazeProblem and MazeAction, so the state is just (row, col).
    #
    # Question: what goes wrong if we create two MazeProblem objects with two different mazes?
    maze: Maze | None = None

    # TODO 1 and 2: write the constructor __init__(self, row, col).
    #         In Python the fields are made inside the constructor, so this one step does both:
    #         save the two values in self.row and self.col.
    #         Python has no "final": do not change them after the state is created.

    # TODO 3: nothing to write here.
    #         Python does not need getters: other classes read state.row and state.col directly.

    # The player reached the goal cell.
    def is_goal(self) -> bool:
        # TODO 4: ask the maze if the cell (row, col) is the goal. Hint: MazeState.maze.is_goal(...)
        return False

    # Draws the maze: P = player, G = goal, # = wall, . = free cell
    def __str__(self) -> str:
        text = ""
        # TODO 5: go over every row r and every col c of the maze (MazeState.maze.rows, .cols).
        #         For each cell, add ONE character to text:
        #           "P" if (r, c) is the player cell
        #           "G" if (r, c) is the goal cell
        #           "." if the cell is free (maze.is_free)
        #           "#" otherwise
        #         After each row, add "\n".
        return text

    # Two states are equal when the player is in the same cell.
    def __eq__(self, other: object) -> bool:
        # TODO 6: 1) return True if other is the same object (self is other)
        #         2) return False if other is not a MazeState (use isinstance)
        #         3) compare row and col
        return False

    # Equal states must give the same number.
    def __hash__(self) -> int:
        # TODO 7: return the cell number. Hint: self.row * MazeState.maze.cols + self.col
        #         Cells are numbered row by row, like seats in a cinema.
        #           cols = 4:  row 0 -> 0 1 2 3,  row 1 -> 4 5 6 7,  row 2 -> 8 9 10 11
        #         Each row has its own block of numbers, so two different cells never
        #         get the same number (no conflicts), for any maze size.
        #         Other option: 31 * row + col (31 is a prime, Java uses it for strings).
        #         Question: find two cells that give the same number with 31 * row + col
        #                   in a maze with 40 columns.
        #         Question: what happens in a set if __eq__ is True but __hash__ is different?
        return 0
