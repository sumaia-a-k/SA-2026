from sa2026.core.state import State


class QueensState(State):
    """
    A state of the 8-queens problem = where the queens are.

    There is ONE queen in every column AND in every row, always.
    rows[c] = the row of the queen in column c (0 = the top row).
      rows = (0, 4, 7, 5, 2, 6, 1, 3)  ->  the queen of column 0 is in row 0,
                                           the queen of column 1 is in row 4, ...
    So two queens can never share a row or a column. Only a DIAGONAL can be a problem.

    A state never changes after it is created. To move, we create a NEW state (see swap).
    """

    def __init__(self, rows):
        # a tuple can not be changed, so nobody can change our queens later
        self._rows: tuple[int, ...] = tuple(rows)

    # the board is n x n (8 for 8-queens)
    def get_size(self) -> int:
        return len(self._rows)

    def get_row(self, col: int) -> int:
        return self._rows[col]

    # a NEW state: the queens of column i and column j change their rows
    def swap(self, i: int, j: int) -> "QueensState":
        new_rows = list(self._rows)
        new_rows[i], new_rows[j] = new_rows[j], new_rows[i]
        return QueensState(new_rows)

    # The number of PAIRS of queens on the same diagonal.
    # Two queens are on the same diagonal when the row distance = the column distance.
    # We count a pair even if another queen stands between them.
    def count_attacking_pairs(self) -> int:
        pairs = 0
        for i in range(len(self._rows)):
            for j in range(i + 1, len(self._rows)):
                if abs(self._rows[i] - self._rows[j]) == j - i:
                    pairs += 1
        return pairs

    # the goal: no two queens attack each other
    def is_goal(self) -> bool:
        return self.count_attacking_pairs() == 0

    # draws the board: Q = a queen, . = an empty square
    def __str__(self) -> str:
        text = ""
        for row in range(len(self._rows)):
            for col in range(len(self._rows)):
                text += " Q" if self._rows[col] == row else " ."
            text += "\n"
        return text

    # two states are equal when every queen is in the same row
    def __eq__(self, other: object) -> bool:
        if self is other:
            return True
        if not isinstance(other, QueensState):
            return False
        return self._rows == other._rows

    def __hash__(self) -> int:
        return hash(self._rows)
