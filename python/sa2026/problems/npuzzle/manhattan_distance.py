from sa2026.core.heuristic_function import HeuristicFunction
from sa2026.core.state import State


class ManhattanDistance(HeuristicFunction):
    """
    h2 = the sum of the Manhattan distances of all tiles to their goal place
    (the empty cell is not counted).

    One move slides one tile one cell, so a tile needs AT LEAST its distance in moves.
    The guess is admissible (and consistent).
    It is never smaller than h1 (MisplacedTiles), so it helps A* more: fewer nodes.
    """

    def get_h(self, s: State) -> float:
        n = s.get_size()
        total = 0
        for i, tile in enumerate(s.get_tiles()):
            if tile == 0:
                continue  # the empty cell is not a tile
            goal_index = tile - 1  # tile 1 belongs at index 0, tile 2 at index 1, ...
            total += abs(i // n - goal_index // n) + abs(i % n - goal_index % n)
        return float(total)
