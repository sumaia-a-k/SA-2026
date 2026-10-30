package sa2026.problems.incomplete_code.npuzzle;

import java.util.Arrays;

import sa2026.core.State;

/**
 * STUDENT TASK: finish this class.
 *
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
 *
 * Search for "TODO" and follow the steps.
 */
public class NpuzzleState implements State {

    private final int[] tiles;    // the board, row by row; 0 = the empty cell
    private final int n;          // the board is n x n
    private final int emptyIndex; // where the 0 is (we find it once, not at every call)

    public NpuzzleState(int[] tiles) {
        // clone() = a copy of the array. The caller can not change our tiles later.
        this.tiles = tiles.clone();
        this.n = (int) Math.sqrt(tiles.length); // exact: NpuzzleProblem checks that the board is n x n

        // TODO 1: find the index of the 0 in the tiles (a for loop) and save it in emptyIndex.
        //         There is only one 0: when you find it, stop the loop with "break".
        //         Question: why do we find it here once, and not in getEmptyRow() every time?
        this.emptyIndex = 0;
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
        // TODO 2: change the index of the empty cell into its row. Hint: index / n
        return 0;
    }

    public int getEmptyCol() {
        // TODO 3: change the index of the empty cell into its col. Hint: index % n
        return 0;
    }

    /*
     * Returns a NEW state: the empty cell moves to (row, col),
     * and the tile that was there slides into the old empty cell.
     * MoveEmptyAction checks the border before it calls this.
     */
    public NpuzzleState moveEmptyTo(int row, int col) {
        // TODO 4: 1) make a copy of the tiles:  int[] newTiles = tiles.clone();
        //         2) find the index of (row, col):  row * n + col
        //         3) in the COPY: put the tile from that index into the empty cell,
        //            and put 0 at that index
        //         4) return new NpuzzleState(newTiles)
        //         Question: what goes wrong if we change "tiles" and not a copy?
        return this;
    }

    // the tiles are 1, 2, 3, ..., n*n-1 and the last cell is empty
    @Override
    public boolean isGoal() {
        // TODO 5: for every index i from 0 to tiles.length - 2:
        //           if tiles[i] is not i + 1, return false.
        //         At the end, return true if the last tile is 0.
        return false;
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
        // TODO 6: 1) return true if o is the same object (this == o)
        //         2) return false if o is not an NpuzzleState (use instanceof)
        //         3) cast o and compare the two arrays with Arrays.equals(tiles, other.tiles)
        //         Question: why is "tiles == other.tiles" wrong here?
        return false;
    }

    // equal states must give the same number
    @Override
    public int hashCode() {
        // TODO 7: return Arrays.hashCode(tiles).
        //         It mixes all the tiles with the prime 31 (like String.hashCode()).
        //         Question: two different boards can get the same number. Is that a problem?
        //         Question: the 15-puzzle has about 10 trillion boards. Can each board get
        //                   its own int number?
        return 0;
    }
}
