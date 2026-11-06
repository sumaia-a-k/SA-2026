package sa2026.problems.npuzzle;

import java.util.ArrayList;
import java.util.List;

import sa2026.core.IAction;
import sa2026.core.Problem;
import sa2026.core.State;

/**
 * The N-puzzle problem (8-puzzle, 15-puzzle, ...): slide the tiles until they are in order.
 *
 * Initial state: the board we get (0 = the empty cell).
 * Goal:          1, 2, 3, ..., n*n-1 and the empty cell at the end.
 * Actions:       move the empty cell up, down, left, right.
 * Cost:          every move costs 1.
 *
 * There is no heuristic yet. We add it in a later session (the 2025 code had the Hamming distance).
 *
 * What we fixed from the 2025 code:
 *  - The start board is checked: it must be n x n, have every number 0 .. n*n-1 once,
 *    and it must be solvable. (Collections.shuffle makes a board with NO solution half of the time,
 *    and then the search looks at every reachable state before it says "no solution".)
 */
public class NpuzzleProblem extends Problem {

    private final State initialState;
    private final List<IAction> actions = new ArrayList<>();

    /*
     * "int..." (varargs): give the tiles row by row, for example
     *   new NpuzzleProblem(4, 1, 2, 5, 8, 3, 7, 6, 0)
     * Throws an IllegalArgumentException if the board is wrong or can not be solved.
     */
    public NpuzzleProblem(int... tiles) {
        check(tiles);
        initialState = new NpuzzleState(tiles);

        // the order of this list is the order the algorithms try the actions
        actions.add(new MoveEmptyAction("Move empty up", -1, 0));
        actions.add(new MoveEmptyAction("Move empty down", 1, 0));
        actions.add(new MoveEmptyAction("Move empty left", 0, -1));
        actions.add(new MoveEmptyAction("Move empty right", 0, 1));
    }

    public static NpuzzleProblem easy() {
        return new NpuzzleProblem(1, 2, 3, 4, 0, 5, 7, 8, 6);   // 2 moves
    }

    public static NpuzzleProblem medium() {
        return new NpuzzleProblem(4, 1, 2, 5, 8, 3, 7, 6, 0);   // 8 moves
    }

    public static NpuzzleProblem hard() {
        return new NpuzzleProblem(1, 8, 3, 2, 6, 4, 7, 0, 5);   // 19 moves
    }

    /*
     * Can this board reach the goal? Only HALF of all boards can.
     * Read the tiles row by row, skip the 0, and count the "inversions":
     * the pairs where a bigger number comes before a smaller one.
     *   n odd  (3 x 3): solvable if the number of inversions is even.
     *   n even (4 x 4): solvable if inversions + (the row of the empty cell,
     *                   counted from the bottom: 1, 2, 3, ...) is odd.
     */
    public static boolean isSolvable(int[] tiles) {
        int n = (int) Math.sqrt(tiles.length);
        int inversions = 0;
        int emptyIndex = 0;
        for (int i = 0; i < tiles.length; i++) {
            if (tiles[i] == 0) {
                emptyIndex = i;
                continue;
            }
            for (int j = i + 1; j < tiles.length; j++) {
                if (tiles[j] != 0 && tiles[i] > tiles[j]) {
                    inversions++;
                }
            }
        }
        if (n % 2 == 1) {
            return inversions % 2 == 0;
        }
        int emptyRowFromBottom = n - emptyIndex / n;
        return (inversions + emptyRowFromBottom) % 2 == 1;
    }

    // checks the start board and throws an error with a clear message if it is wrong
    private static void check(int[] tiles) {
        int n = (int) Math.sqrt(tiles.length);
        if (n < 2 || n * n != tiles.length) {
            throw new IllegalArgumentException(
                    "The board must be n x n (4, 9, 16, ... numbers), not " + tiles.length + " numbers.");
        }
        boolean[] seen = new boolean[tiles.length];
        for (int t : tiles) {
            if (t < 0 || t >= tiles.length || seen[t]) {
                throw new IllegalArgumentException(
                        "Each number from 0 to " + (tiles.length - 1) + " must be on the board once.");
            }
            seen[t] = true;
        }
        if (!isSolvable(tiles)) {
            throw new IllegalArgumentException("This board can never be solved (see isSolvable()).");
        }
    }

    @Override
    public State getInitialState() {
        return initialState;
    }

    @Override
    public boolean isGoal(State state) {
        return state.isGoal();
    }

    @Override
    public List<IAction> getActions() {
        return actions;
    }

    // every move costs the same
    @Override
    public double getActionCost(State s, IAction a, State next) {
        return 1;
    }
}
