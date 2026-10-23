class Maze:
    """
    The maze map: a grid of free cells and walls, with a start cell and a goal cell.

    A maze is made from text lines. Each character is one cell:
      '#' = wall      '.' = free cell      'S' = start      'G' = goal

    The maze never changes after it is created, so many states can share it.
    """

    # Creates a maze from text lines, for example: Maze.from_lines("S.#", "..G")
    #
    # "*lines" means: give me any number of strings (like "String..." in Java).
    # Python puts them in a tuple for us, so inside the method "lines" is a tuple.
    # These two calls are the same:
    #   Maze.from_lines("S.#", "..G")
    #   Maze.from_lines(*["S.#", "..G"])
    #
    # @staticmethod = the method belongs to the class, not to one object (like "static" in Java).
    @staticmethod
    def from_lines(*lines: str) -> "Maze":
        return Maze(lines)

    # Java makes this constructor private. Python has no private constructors,
    # so please create mazes with Maze.from_lines(...).
    def __init__(self, lines):
        if len(lines) == 0:
            raise ValueError("The maze has no rows.")
        self.rows = len(lines)
        self.cols = len(lines[0])
        self._walls = []  # _walls[row][col] is True if the cell is a wall

        # set below, when we find 'S' and 'G'
        self.start_row = 0
        self.start_col = 0
        self.goal_row = 0
        self.goal_col = 0

        found_start = False
        found_goal = False

        for row in range(self.rows):
            if len(lines[row]) != self.cols:
                raise ValueError(f"Row {row} has a different length.")
            row_walls = [False] * self.cols  # a new row with no walls yet
            for col in range(self.cols):
                cell = lines[row][col]
                if cell == "#":
                    row_walls[col] = True
                elif cell == "S":
                    self.start_row = row
                    self.start_col = col
                    found_start = True
                elif cell == "G":
                    self.goal_row = row
                    self.goal_col = col
                    found_goal = True
                elif cell != ".":
                    raise ValueError(f"Unknown symbol '{cell}' at {row},{col}")
            self._walls.append(row_walls)

        if not found_start or not found_goal:
            raise ValueError("The maze needs one 'S' and one 'G'.")

    # True if the cell is inside the maze and is not a wall
    def is_free(self, row: int, col: int) -> bool:
        if row < 0 or row >= self.rows or col < 0 or col >= self.cols:
            return False  # outside the maze
        return not self._walls[row][col]

    def is_goal(self, row: int, col: int) -> bool:
        return row == self.goal_row and col == self.goal_col
