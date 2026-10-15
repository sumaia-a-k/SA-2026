package sa2026.problems.incomplete_code.maze;

import java.util.Collection;

import sa2026.core.IAction;
import sa2026.core.Problem;
import sa2026.core.State;

/**
 * A small demo of the maze problem. There is no search algorithm yet.
 * We only check that the state, the actions and the goal test work.
 *
 * How to run (inside the SA-2026 folder, NOT its parent folder):
 *   1. Compile:  .\run.bat   (Windows)   or   ./run.sh   (Git Bash, macOS, Linux)
 *   2. Run:      java -cp out sa2026.problems.incomplete_code.maze.MazeDemo
 * Compile again after every change, or Java runs the old code.
 * In VS Code you can also click "Run" above main().
 */
public class MazeDemo {

    public static void main(String[] args) {
        Maze maze = Maze.fromLines(
                "S.#....",
                ".##.##.",
                "....#..",
                ".##....",
                "...#.#G");

        Problem problem = new MazeProblem(maze);
        State start = problem.getInitialState();

        System.out.println("=== Initial state ===");
        System.out.println(start);
        System.out.println("Is it a goal? " + problem.isGoal(start));

        // try every action on the initial state
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

        // walk by hand to the goal: down 2, right 3, down 1, right 3, down 1
        System.out.println("=== Walk by hand to the goal ===");
        String[] path = {"Move down", "Move down",
                         "Move right", "Move right", "Move right",
                         "Move down",
                         "Move right", "Move right", "Move right",
                         "Move down"};
        State current = start;
        for (String step : path) {
            current = applyByName(problem, current, step);
            if (current == null) {
                System.out.println("Stopped: \"" + step + "\" is not allowed here.");
                return;
            }
        }
        System.out.println(current);
        System.out.println("Is it a goal? " + problem.isGoal(current));
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
