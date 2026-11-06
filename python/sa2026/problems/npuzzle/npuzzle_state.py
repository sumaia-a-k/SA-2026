import math

from sa2026.core.state import State


class NpuzzleState(State):
    """
    A state of the N-puzzle = where every tile is.

    We keep the board in ONE tuple, row by row. 0 = the empty cell.
      4 1 2
      5 8 3    ->  tiles = (4, 1, 2, 5, 8, 3, 7, 6, 0)
      7 6 _
    index = row * n + col,   row = index // n,   col = index % n

    Goal: (1, 2, 3, ..., n*n-1, 0) (the empty cell at the end).

    A state never changes after it is created.
    To make a move, we create a NEW state (see move_empty_to).
    """

    def __init__(self, tiles):
        # A tuple can not be changed (a list can). So nobody can change our tiles later,
        # like "final" + clone() in Java. tuple(...) also makes a list into a tuple.
        self._tiles: tuple[int, ...] = tuple(tiles)
        self._n = math.isqrt(len(self._tiles))  # n x n board; isqrt = the whole-number square root
        self._empty_index = self._tiles.index(0)  # where the 0 is (we find it once; index() stops at the first 0)

    # the board is n x n
    def get_size(self) -> int:
        return self._n

    def get_tile(self, row: int, col: int) -> int:
        return self._tiles[row * self._n + col]

    # the tiles (a tuple, so the caller can not change this state)
    def get_tiles(self) -> tuple[int, ...]:
        return self._tiles

    def get_empty_row(self) -> int:
        return self._empty_index // self._n

    def get_empty_col(self) -> int:
        return self._empty_index % self._n

    # Returns a NEW state: the empty cell moves to (row, col),
    # and the tile that was there slides into the old empty cell.
    # MoveEmptyAction checks the border before it calls this.
    def move_empty_to(self, row: int, col: int) -> "NpuzzleState":
        new_tiles = list(self._tiles)                          # a list copy, so we can change it
        target = row * self._n + col
        new_tiles[self._empty_index] = new_tiles[target]       # the tile slides into the empty cell
        new_tiles[target] = 0                                  # its old cell is empty now
        return NpuzzleState(new_tiles)

    # the tiles are 1, 2, 3, ..., n*n-1 and the last cell is empty
    def is_goal(self) -> bool:
        for i in range(len(self._tiles) - 1):
            if self._tiles[i] != i + 1:
                return False
        return self._tiles[-1] == 0

    # draws the board; "_" = the empty cell
    def __str__(self) -> str:
        text = ""
        for i, tile in enumerate(self._tiles):
            text += "  _" if tile == 0 else f"{tile:3}"
            if (i + 1) % self._n == 0:
                text += "\n"
        return text

    # two states are equal when all the tiles are in the same places
    def __eq__(self, other: object) -> bool:
        if self is other:
            return True
        if not isinstance(other, NpuzzleState):
            return False
        return self._tiles == other._tiles  # == on two tuples compares the numbers

    # The Python hash of a tuple mixes all the tiles (like Arrays.hashCode() in Java).
    # Two different boards can get the same number (a conflict). It is rare,
    # and then __eq__ decides.
    def __hash__(self) -> int:
        return hash(self._tiles)
