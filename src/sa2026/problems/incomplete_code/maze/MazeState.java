package sa2026.problems.incomplete_code.maze;

import sa2026.core.State;

/**
 * STUDENT TASK: finish this class.
 *
 * A state of the maze problem = where the player is now (row, col).
 * Only row and col are the state.
 *
 * Search for "TODO" and follow the steps.
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
     *
     * Question: what goes wrong if we create two MazeProblem objects with two different mazes?
     */
    private static Maze maze;

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

    // TODO 1: add two final fields: the row and the col of the player.


    // TODO 2: write the constructor MazeState(int row, int col).
    //         Save the two values in the fields.


    // TODO 3: write the getters getRow() and getCol().


    // The player reached the goal cell.
    @Override
    public boolean isGoal() {
        // TODO 4: ask the maze if the cell (row, col) is the goal. Hint: maze.isGoal(...)
        return false;
    }

    // Draws the maze: P = player, G = goal, # = wall, . = free cell
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        // TODO 5: go over every row r and every col c of the maze (maze.getRows(), maze.getCols()).
        //         For each cell, add ONE character to sb:
        //           'P' if (r, c) is the player cell
        //           'G' if (r, c) is the goal cell
        //           '.' if the cell is free (maze.isFree)
        //           '#' otherwise
        //         After each row, add '\n'.
        return sb.toString();
    }

    // Two states are equal when the player is in the same cell.
    @Override
    public boolean equals(Object o) {
        // TODO 6: 1) return true if o is the same object (this == o)
        //         2) return false if o is not a MazeState (use instanceof)
        //         3) cast o to MazeState and compare row and col
        return false;
    }

    // Equal states must give the same number.
    @Override
    public int hashCode() {
        // TODO 7: return the cell number. Hint: row * maze.getCols() + col
        //         Cells are numbered row by row, like seats in a cinema.
        //           cols = 4:  row 0 -> 0 1 2 3,  row 1 -> 4 5 6 7,  row 2 -> 8 9 10 11
        //         Each row has its own block of numbers, so two different cells never
        //         get the same number (no conflicts), for any maze size.
        //         Other option: 31 * row + col (31 is a prime, Java uses it in String.hashCode()).
        //         Question: find two cells that give the same number with 31 * row + col
        //                   in a maze with 40 columns.
        //         Question: what happens in a HashSet if equals() is true but hashCode() is different?
        return 0;
    }
}
