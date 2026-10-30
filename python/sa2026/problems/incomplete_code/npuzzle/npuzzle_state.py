import math

from sa2026.core.state import State


class NpuzzleState(State):
    """
    STUDENT TASK: finish this class.

    A state of the N-puzzle = where every tile is.

    We keep the board in ONE tuple, row by row. 0 = the empty cell.
      4 1 2
      5 8 3    ->  tiles = (4, 1, 2, 5, 8, 3, 7, 6, 0)
      7 6 _
    index = row * n + col,   row = index // n,   col = index % n

    Goal: (1, 2, 3, ..., n*n-1, 0) (the empty cell at the end).

    A state never changes after it is created.
    To make a move, we create a NEW state (see move_empty_to).

    Search for "TODO" and follow the steps.
    """

    def __init__(self, tiles):
        # A tuple can not be changed (a list can). So nobody can change our tiles later,
        # like "final" + clone() in Java. tuple(...) also makes a list into a tuple.
        self._tiles: tuple[int, ...] = tuple(tiles)
        self._n = math.isqrt(len(self._tiles))  # n x n board; isqrt = the whole-number square root

        # TODO 1: find where the 0 is and save it in self._empty_index.
        #         Hint: a tuple has the method index(): self._tiles.index(0)
        #         Question: why do we find it here once, and not in get_empty_row() every time?
        self._empty_index = 0

    # the board is n x n
    def get_size(self) -> int:
        return self._n

    def get_tile(self, row: int, col: int) -> int:
        return self._tiles[row * self._n + col]

    # the tiles (a tuple, so the caller can not change this state)
    def get_tiles(self) -> tuple[int, ...]:
        return self._tiles

    def get_empty_row(self) -> int:
        # TODO 2: change the index of the empty cell into its row. Hint: index // n
        return 0

    def get_empty_col(self) -> int:
        # TODO 3: change the index of the empty cell into its col. Hint: index % n
        return 0

    # Returns a NEW state: the empty cell moves to (row, col),
    # and the tile that was there slides into the old empty cell.
    # MoveEmptyAction checks the border before it calls this.
    def move_empty_to(self, row: int, col: int) -> "NpuzzleState":
        # TODO 4: 1) make a list copy of the tiles:  new_tiles = list(self._tiles)
        #         2) find the index of (row, col):  row * self._n + col
        #         3) in the COPY: put the tile from that index into the empty cell,
        #            and put 0 at that index
        #         4) return NpuzzleState(new_tiles)
        #         Question: why can we not change self._tiles directly?
        return self

    # the tiles are 1, 2, 3, ..., n*n-1 and the last cell is empty
    def is_goal(self) -> bool:
        # TODO 5: for every index i from 0 to len(self._tiles) - 2:
        #           if self._tiles[i] is not i + 1, return False.
        #         At the end, return True if the last tile is 0 (self._tiles[-1]).
        return False

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
        # TODO 6: 1) return True if other is the same object (self is other)
        #         2) return False if other is not an NpuzzleState (use isinstance)
        #         3) compare the two tuples with ==
        return False

    # equal states must give the same number
    def __hash__(self) -> int:
        # TODO 7: return hash(self._tiles), the Python hash of the tuple.
        #         Question: two different boards can get the same number. Is that a problem?
        return 0
