package sa2026.problems.maze;

import sa2026.core.State;

/**
 * A state of the maze problem = where the player is now (row, col).
 * Only row and col are the state.
 */
public class MazeState implements State {

    /*
     * The maze is NOT part of the state. The walls and the goal never change.
     * We keep it here only to check the goal and to draw the state.
     *
     * It is static: there is ONE maze for all states, not one per state.
     * So it takes no extra memory per state. It is not used in equals(); hashCode() only reads its number of columns.
     * Limit: we can work with only one maze at a time. A new maze replaces the old one.
     *
     * Other options:
     *  1. A normal (non-static) field: each state keeps a reference to the same maze.
     *     It costs only one reference per state, and we can have many mazes.
     *  2. Keep the maze only in MazeProblem and MazeAction, so the state is just (row, col).
     *     but in this case we will have limitation in drawing the maze in its current state
     */
    private static Maze maze;

    private final int row;
    private final int col;

    public MazeState(int row, int col) {
        this.row = row;
        this.col = col;
    }

    /*
     * MazeProblem calls this once, before the search starts.
     * This line does NOT copy the maze. It copies the reference,
     * so "maze" points to the same original Maze object.
     */
    public static void setMaze(Maze newMaze) {
        maze = newMaze;
    }

    public static Maze getMaze() {
        return maze;
    }

    public int getRow() {
        return row;
    }

    public int getCol() {
        return col;
    }

    // the player reached the goal cell
    @Override
    public boolean isGoal() {
        return maze.isGoal(row, col);
    }

    // draws the maze: P = player, G = goal, # = wall, . = free cell
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int r = 0; r < maze.getRows(); r++) {
            for (int c = 0; c < maze.getCols(); c++) {
                if (r == row && c == col) {
                    sb.append('P');
                } else if (maze.isGoal(r, c)) {
                    sb.append('G');
                } else if (maze.isFree(r, c)) {
                    sb.append('.');
                } else {
                    sb.append('#');
                }
            }
            sb.append('\n');
        }
        return sb.toString();
    }

    // two states are equal when the player is in the same cell
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof MazeState)) return false;
        MazeState other = (MazeState) o;
        return row == other.row && col == other.col;
    }

    /*
     * Equal states must give the same number.
     * We use the cell number: cells are numbered row by row, like seats in a cinema.
     *   cols = 4:  row 0 -> 0 1 2 3,  row 1 -> 4 5 6 7,  row 2 -> 8 9 10 11
     * Each row has its own block of numbers, so two different cells never get
     * the same number (no conflicts), for any maze size.
     *
     * Other option: 31 * row + col (31 is a prime, Java uses it in String.hashCode()).
     * Primes are good when we do not know the ranges of the values.
     * Here we know them (0 <= col < cols), so we can have no conflicts at all.
     */
    @Override
    public int hashCode() {
        return row * maze.getCols() + col;
    }
}
