package sa2026.problems.queens;

import java.util.Arrays;

import sa2026.core.State;

/**
 * A state of the 8-queens problem = where the queens are.
 *
 * There is ONE queen in every column AND in every row, always.
 * rows[c] = the row of the queen in column c (0 = the top row).
 *   rows = {0, 4, 7, 5, 2, 6, 1, 3}  ->  the queen of column 0 is in row 0,
 *                                        the queen of column 1 is in row 4, ...
 * So two queens can never share a row or a column. Only a DIAGONAL can be a problem.
 *
 * A state never changes after it is created. To move, we create a NEW state (see swap).
 */
public class QueensState implements State {

    private final int[] rows; // rows[c] = the row of the queen in column c

    public QueensState(int[] rows) {
        this.rows = rows.clone(); // a copy: the caller can not change our queens later
    }

    // the board is n x n (8 for 8-queens)
    public int getSize() {
        return rows.length;
    }

    public int getRow(int col) {
        return rows[col];
    }

    // a NEW state: the queens of column i and column j change their rows
    public QueensState swap(int i, int j) {
        int[] newRows = rows.clone();
        newRows[i] = rows[j];
        newRows[j] = rows[i];
        return new QueensState(newRows);
    }

    /*
     * The number of PAIRS of queens on the same diagonal.
     * Two queens are on the same diagonal when the row distance = the column distance.
     * We count a pair even if another queen stands between them.
     */
    public int countAttackingPairs() {
        int pairs = 0;
        for (int i = 0; i < rows.length; i++) {
            for (int j = i + 1; j < rows.length; j++) {
                if (Math.abs(rows[i] - rows[j]) == j - i) {
                    pairs++;
                }
            }
        }
        return pairs;
    }

    // the goal: no two queens attack each other
    @Override
    public boolean isGoal() {
        return countAttackingPairs() == 0;
    }

    // draws the board: Q = a queen, . = an empty square
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int row = 0; row < rows.length; row++) {
            for (int col = 0; col < rows.length; col++) {
                sb.append(rows[col] == row ? " Q" : " .");
            }
            sb.append('\n');
        }
        return sb.toString();
    }

    // two states are equal when every queen is in the same row
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof QueensState)) return false;
        return Arrays.equals(rows, ((QueensState) o).rows);
    }

    @Override
    public int hashCode() {
        return Arrays.hashCode(rows);
    }
}
