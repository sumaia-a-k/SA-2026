package sa2026.problems.incomplete_code.npuzzle;

import java.util.Arrays;
import java.util.Collection;

import sa2026.algorithms.BFS;
import sa2026.core.IAction;
import sa2026.core.Node;
import sa2026.core.Problem;
import sa2026.core.State;

/**
 * A small demo of the N-puzzle problem.
 * We check that the state, the actions and the goal test work,
 * and at the end we let BFS solve one board.
 *
 * How to run (inside the SA-2026 folder, NOT its parent folder):
 *   1. Compile:  .\run.bat   (Windows)   or   ./run.sh   (Git Bash, macOS, Linux)
 *   2. Run:      java -cp out sa2026.problems.incomplete_code.npuzzle.NpuzzleDemo
 * Compile again after every change, or Java runs the old code.
 * In VS Code you can also click "Run" above main().
 */
public class NpuzzleDemo {

    public static void main(String[] args) {
        Problem problem = NpuzzleProblem.medium();
        State start = problem.getInitialState();

        System.out.println("=== Initial state (the medium test) ===");
        System.out.println(start);
        System.out.println("Is it a goal? " + problem.isGoal(start));

        // try every action on the initial state (the empty cell is in a corner)
        System.out.println("\n=== Try each action on the initial state ===");
        for (IAction action : problem.getActions()) {
            Collection<State> result = action.apply(start);
            if (result.isEmpty()) {
                System.out.println(action.getName() + ": not allowed\n");
            } else {
                System.out.println(action.getName() + ": allowed");
                System.out.println(result.iterator().next());
            }
        }

        // walk by hand: the easy test needs 2 moves
        System.out.println("=== Walk by hand: the easy test ===");
        Problem easy = NpuzzleProblem.easy();
        State current = easy.getInitialState();
        System.out.println(current);
        for (String step : new String[] {"Move empty right", "Move empty down"}) {
            current = applyByName(easy, current, step);
            if (current == null) {
                System.out.println("Stopped: \"" + step + "\" is not allowed here.");
                return;
            }
            System.out.println(step + ":");
            System.out.println(current);
        }
        System.out.println("Is it a goal? " + easy.isGoal(current));

        // only half of all boards can be solved
        System.out.println("\n=== Can these boards be solved? ===");
        int[][] boards = {{1, 2, 3, 4, 5, 6, 7, 0, 8}, {1, 2, 3, 4, 5, 6, 8, 7, 0}};
        for (int[] board : boards) {
            System.out.println(Arrays.toString(board) + ": " + NpuzzleProblem.isSolvable(board));
        }
        try {
            new NpuzzleProblem(1, 2, 3, 4, 5, 6, 8, 7, 0);
        } catch (IllegalArgumentException e) {
            System.out.println("NpuzzleProblem(...) says: " + e.getMessage());
        }

        // now a search algorithm can solve it
        System.out.println("\n=== BFS (graph search) solves the medium test ===");
        BFS bfs = new BFS(true);
        Node goal = problem.solve(bfs);
        StringBuilder moves = new StringBuilder();
        for (Node node : goal.getPathFromRoot()) {
            if (node.getAction() != null) {
                moves.append(moves.length() == 0 ? "" : ", ").append(node.getAction().getName());
            }
        }
        System.out.println("Moves: " + moves);
        System.out.println("Steps: " + goal.getDepth() + ", expanded: " + bfs.getNodesActuallyExpanded()
                + ", generated: " + bfs.getGeneratedNodes());
    }

    // finds the action with this name and applies it on the state
    private static State applyByName(Problem problem, State state, String name) {
        for (IAction action : problem.getActions()) {
            if (action.getName().equals(name)) {
                Collection<State> result = action.apply(state);
                return result.isEmpty() ? null : result.iterator().next();
            }
        }
        return null;
    }
}
