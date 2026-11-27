package sa2026.problems.npuzzle;

import sa2026.core.HeuristicFunction;
import sa2026.core.State;

/**
 * h2 = the sum of the Manhattan distances of all tiles to their goal place
 * (the empty cell is not counted).
 *
 * One move slides one tile one cell, so a tile needs AT LEAST its distance in moves.
 * The guess is admissible (and consistent).
 * It is never smaller than h1 (MisplacedTiles), so it helps A* more: fewer nodes.
 */
public class ManhattanDistance implements HeuristicFunction {

    @Override
    public double getH(State s) {
        NpuzzleState board = (NpuzzleState) s;
        int n = board.getSize();
        int[] tiles = board.getTiles();
        int sum = 0;
        for (int i = 0; i < tiles.length; i++) {
            int tile = tiles[i];
            if (tile == 0) {
                continue; // the empty cell is not a tile
            }
            int goalIndex = tile - 1; // tile 1 belongs at index 0, tile 2 at index 1, ...
            sum += Math.abs(i / n - goalIndex / n) + Math.abs(i % n - goalIndex % n);
        }
        return sum;
    }
}
