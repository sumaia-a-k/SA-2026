package sa2026.problems.queens;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

import sa2026.core.HeuristicFunction;
import sa2026.core.IAction;
import sa2026.core.Problem;
import sa2026.core.State;

/**
 * The 8-queens problem: put 8 queens on a chess board so that no two attack each other.
 * (A queen attacks along its row, its column and its two diagonals.)
 *
 * Initial state: a board with one queen in every row and every column (see QueensState).
 * Goal:          no two queens on the same diagonal (h = 0).
 * Actions:       swap two queens (28 neighbours).
 * Cost:          every swap costs 1. (We do not care about the path, only about the final board.)
 * Heuristic:     DiagonalAttacks: the number of pairs of queens on the same diagonal.
 *
 * This problem is for local search (Hill Climbing). It can also make a random start state
 * (getRandomState), so RandomRestart can use it.
 */
public class QueensProblem extends Problem {

    private final State initialState;
    private final List<IAction> actions = new ArrayList<>();
    private final HeuristicFunction heuristic = new DiagonalAttacks();

    /*
     * "int..." (varargs): give the row of the queen of each column, for example
     *   new QueensProblem(0, 1, 3, 4, 5, 2, 7, 6)
     * Every row from 0 to n-1 must be used once (one queen in every row).
     */
    public QueensProblem(int... rows) {
        check(rows);
        initialState = new QueensState(rows);
        actions.add(new SwapQueensAction());
    }

    // Example 1 of the lesson page: h = 9, Hill Climbing solves it in 3 swaps
    public static QueensProblem example1() {
        return new QueensProblem(0, 1, 3, 4, 5, 2, 7, 6);
    }

    // Example 2 of the lesson page: h = 9, Hill Climbing gets stuck at h = 1 (a flat place)
    public static QueensProblem example2() {
        return new QueensProblem(0, 1, 2, 5, 6, 7, 4, 3);
    }

    // checks the board and throws an error with a clear message if it is wrong
    private static void check(int[] rows) {
        if (rows.length < 1) {
            throw new IllegalArgumentException("The board needs at least one queen.");
        }
        boolean[] used = new boolean[rows.length];
        for (int r : rows) {
            if (r < 0 || r >= rows.length || used[r]) {
                throw new IllegalArgumentException(
                        "Each row from 0 to " + (rows.length - 1) + " must have exactly one queen.");
            }
            used[r] = true;
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

    // every swap costs the same
    @Override
    public double getActionCost(State s, IAction a, State next) {
        return 1;
    }

    @Override
    public HeuristicFunction getHeuristicFunction() {
        return heuristic;
    }

    // a random board of the same size: the rows 0, 1, ..., n-1 in a random order
    @Override
    public State getRandomState(Random random) {
        int n = ((QueensState) initialState).getSize();
        List<Integer> rows = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            rows.add(i);
        }
        // mix the rows, like shuffling cards
        Collections.shuffle(rows, random);
        int[] board = new int[n];
        for (int i = 0; i < n; i++) {
            board[i] = rows.get(i);
        }
        return new QueensState(board);
    }
}
