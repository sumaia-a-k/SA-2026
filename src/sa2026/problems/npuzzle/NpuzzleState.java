package sa2026.problems.npuzzle;

import java.util.Arrays;

import sa2026.core.State;

/**
 * A state of the N-puzzle = where every tile is.
 *
 * We keep the board in ONE array, row by row. 0 = the empty cell.
 *   4 1 2
 *   5 8 3    ->  tiles = {4, 1, 2, 5, 8, 3, 7, 6, 0}
 *   7 6 _
 * index = row * n + col,   row = index / n,   col = index % n
 *
 * Goal: {1, 2, 3, ..., n*n-1, 0} (the empty cell at the end).
 *
 * A state never changes after it is created: there are no setters.
 * To make a move, we create a NEW state (see moveEmptyTo).
 */
public class NpuzzleState implements State {

    private final int[] tiles;    // the board, row by row; 0 = the empty cell
    private final int n;          // the board is n x n
    private final int emptyIndex; // where the 0 is (we find it once, not at every call)

    public NpuzzleState(int[] tiles) {
        // clone() = a copy of the array. The caller can not change our tiles later.
        this.tiles = tiles.clone();
        this.n = (int) Math.sqrt(tiles.length); // exact: NpuzzleProblem checks that the board is n x n

        int empty = -1;
        for (int i = 0; i < tiles.length; i++) {
            if (tiles[i] == 0) {
                empty = i;
                break; // there is only one 0, so we can stop here
            }
        }
        this.emptyIndex = empty;
    }

    // the board is n x n
    public int getSize() {
        return n;
    }

    public int getTile(int row, int col) {
        return tiles[row * n + col];
    }

    // a copy of the tiles, so the caller can not change this state
    public int[] getTiles() {
        return tiles.clone();
    }

    public int getEmptyRow() {
        return emptyIndex / n;
    }

    public int getEmptyCol() {
        return emptyIndex % n;
    }

    /*
     * Returns a NEW state: the empty cell moves to (row, col),
     * and the tile that was there slides into the old empty cell.
     * MoveEmptyAction checks the border before it calls this.
     */
    public NpuzzleState moveEmptyTo(int row, int col) {
        int[] newTiles = tiles.clone();          // never change this state: work on a copy
        int target = row * n + col;
        newTiles[emptyIndex] = newTiles[target]; // the tile slides into the empty cell
        newTiles[target] = 0;                    // its old cell is empty now
        return new NpuzzleState(newTiles);
    }

    // the tiles are 1, 2, 3, ..., n*n-1 and the last cell is empty
    @Override
    public boolean isGoal() {
        for (int i = 0; i < tiles.length - 1; i++) {
            if (tiles[i] != i + 1) {
                return false;
            }
        }
        return tiles[tiles.length - 1] == 0;
    }

    // draws the board; "_" = the empty cell
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < tiles.length; i++) {
            sb.append(tiles[i] == 0 ? "  _" : String.format("%3d", tiles[i]));
            if ((i + 1) % n == 0) {
                sb.append('\n');
            }
        }
        return sb.toString();
    }

    // two states are equal when all the tiles are in the same places
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof NpuzzleState)) return false;
        NpuzzleState other = (NpuzzleState) o;
        return Arrays.equals(tiles, other.tiles); // compares the numbers, not the arrays
    }

    /*
     * Arrays.hashCode() mixes all the tiles with the prime 31 (like String.hashCode()).
     * Two different boards can get the same number (a conflict). It is rare,
     * and then equals() decides. We can not give every board its own number:
     * the 15-puzzle has about 10 trillion boards, but an int has only about 4 billion values.
     */
    @Override
    public int hashCode() {
        return Arrays.hashCode(tiles);
    }
}
