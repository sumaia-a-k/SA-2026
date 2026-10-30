package sa2026.problems.incomplete_code.npuzzle;

import java.util.ArrayList;
import java.util.List;

import sa2026.core.IAction;
import sa2026.core.Problem;
import sa2026.core.State;

/**
 * STUDENT TASK: finish this class.
 *
 * The N-puzzle problem (8-puzzle, 15-puzzle, ...): slide the tiles until they are in order.
 *
 * Initial state: the board we get (0 = the empty cell).
 * Goal:          1, 2, 3, ..., n*n-1 and the empty cell at the end.
 * Actions:       move the empty cell up, down, left, right.
 * Cost:          every move costs 1.
 *
 * There is no heuristic yet. We add it in a later session.
 *
 * Search for "TODO" and follow the steps.
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

        // TODO 1: create the initial state from the tiles. Hint: new NpuzzleState(tiles)
        initialState = null;

        // TODO 2: add the four actions to the list "actions".
        //         Use these names and changes of the EMPTY cell (rowChange, colChange):
        //           "Move empty up"    (-1,  0)
        //           "Move empty down"  ( 1,  0)
        //           "Move empty left"  ( 0, -1)
        //           "Move empty right" ( 0,  1)
        //         The order of this list is the order the algorithms try the actions.
    }

    // the three tests from the 2025 code
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
        // TODO 7 (a bit harder): count the inversions.
        //   For every i, and every j > i: if tiles[i] and tiles[j] are not 0
        //   and tiles[i] > tiles[j], it is one inversion.
        //   Then use the rules above. n = (int) Math.sqrt(tiles.length)
        //   Check: {1, 2, 3, 4, 5, 6, 8, 7, 0} has 1 inversion, so it can NOT be solved.
        //   Question: why does a move left or right never change the number of inversions?
        return true;
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
        // TODO 3: return the initial state.
        return null;
    }

    @Override
    public boolean isGoal(State state) {
        // TODO 4: ask the state if it is a goal.
        return false;
    }

    @Override
    public List<IAction> getActions() {
        // TODO 5: return the list of actions.
        return null;
    }

    // The cost of going from state s to state next using action a.
    @Override
    public double getActionCost(State s, IAction a, State next) {
        // TODO 6: every move costs the same. Return 1.
        return 0;
    }
}
