from sa2026.core.state import State
from sa2026.problems.maze.maze import Maze


class MazeState(State):
    """
    A state of the maze problem = where the player is now (row, col).
    Only row and col are the state.
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
    #     But then it is harder to draw the maze with the player in it.
    maze: Maze | None = None

    def __init__(self, row: int, col: int):
        # Python has no "final". Do not change row and col after the state is created:
        # states are kept in sets, and a state that changes gets lost inside the set.
        self.row = row
        self.col = col

    # the player reached the goal cell
    def is_goal(self) -> bool:
        return MazeState.maze.is_goal(self.row, self.col)

    # draws the maze: P = player, G = goal, # = wall, . = free cell
    def __str__(self) -> str:
        maze = MazeState.maze
        text = ""
        for r in range(maze.rows):
            for c in range(maze.cols):
                if r == self.row and c == self.col:
                    text += "P"
                elif maze.is_goal(r, c):
                    text += "G"
                elif maze.is_free(r, c):
                    text += "."
                else:
                    text += "#"
            text += "\n"
        return text

    # two states are equal when the player is in the same cell
    def __eq__(self, other: object) -> bool:
        if self is other:
            return True
        if not isinstance(other, MazeState):
            return False
        return self.row == other.row and self.col == other.col

    # Equal states must give the same number.
    # We use the cell number: cells are numbered row by row, like seats in a cinema.
    #   cols = 4:  row 0 -> 0 1 2 3,  row 1 -> 4 5 6 7,  row 2 -> 8 9 10 11
    # Each row has its own block of numbers, so two different cells never get
    # the same number (no conflicts), for any maze size.
    #
    # Other option: hash((self.row, self.col)), the Python hash of a tuple.
    # It is good when we do not know the ranges of the values.
    # Here we know them (0 <= col < cols), so we can have no conflicts at all.
    def __hash__(self) -> int:
        return self.row * MazeState.maze.cols + self.col
