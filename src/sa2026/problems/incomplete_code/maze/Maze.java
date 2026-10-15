package sa2026.problems.incomplete_code.maze;

/**
 * The maze map: a grid of free cells and walls, with a start cell and a goal cell.
 *
 * A maze is made from text lines. Each character is one cell:
 *   '#' = wall      '.' = free cell      'S' = start      'G' = goal
 *
 * The maze never changes after it is created, so many states can share it.
 */
public class Maze {

    private final boolean[][] walls; // walls[row][col] is true if the cell is a wall
    private final int rows;
    private final int cols;
    private int startRow, startCol;
    private int goalRow, goalCol;

    /*
     * Creates a maze from text lines, for example: Maze.fromLines("S.#", "..G")
     *
     * "String..." (varargs) means: give me any number of Strings.
     * Java puts them in an array for us, so inside the method "lines" is a String[].
     * These two calls are the same:
     *   Maze.fromLines("S.#", "..G");
     *   Maze.fromLines(new String[] {"S.#", "..G"});
     */
    public static Maze fromLines(String... lines) {
        return new Maze(lines);
    }

    private Maze(String[] lines) {
        if (lines.length == 0) {
            throw new IllegalArgumentException("The maze has no rows.");
        }
        rows = lines.length;
        cols = lines[0].length();
        walls = new boolean[rows][cols];

        boolean foundStart = false;
        boolean foundGoal = false;

        for (int row = 0; row < rows; row++) {
            if (lines[row].length() != cols) {
                throw new IllegalArgumentException("Row " + row + " has a different length.");
            }
            for (int col = 0; col < cols; col++) {
                char cell = lines[row].charAt(col);
                if (cell == '#') {
                    walls[row][col] = true;
                } else if (cell == 'S') {
                    startRow = row;
                    startCol = col;
                    foundStart = true;
                } else if (cell == 'G') {
                    goalRow = row;
                    goalCol = col;
                    foundGoal = true;
                } else if (cell != '.') {
                    throw new IllegalArgumentException("Unknown symbol '" + cell + "' at " + row + "," + col);
                }
            }
        }
        if (!foundStart || !foundGoal) {
            throw new IllegalArgumentException("The maze needs one 'S' and one 'G'.");
        }
    }

    public int getRows() {
        return rows;
    }

    public int getCols() {
        return cols;
    }

    public int getStartRow() {
        return startRow;
    }

    public int getStartCol() {
        return startCol;
    }

    public int getGoalRow() {
        return goalRow;
    }

    public int getGoalCol() {
        return goalCol;
    }

    // true if the cell is inside the maze and is not a wall
    public boolean isFree(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            return false; // outside the maze
        }
        return !walls[row][col];
    }

    public boolean isGoal(int row, int col) {
        return row == goalRow && col == goalCol;
    }
}
