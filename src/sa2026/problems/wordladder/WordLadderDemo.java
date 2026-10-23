package sa2026.problems.wordladder;

import java.util.Collection;

import sa2026.core.IAction;
import sa2026.core.Problem;
import sa2026.core.State;

/**
 * A small demo of the word ladder problem. There is no search algorithm yet.
 * We only check that the state, the action and the goal test work.
 *
 * How to run (inside the SA-2026 folder, NOT its parent folder):
 *   1. Compile:  .\run.bat   (Windows)   or   ./run.sh   (Git Bash, macOS, Linux)
 *   2. Run:      java -cp out sa2026.problems.wordladder.WordLadderDemo
 * Compile again after every change, or Java runs the old code.
 * In VS Code you can also click "Run" above main().
 */
public class WordLadderDemo {

    public static void main(String[] args) {
        Problem problem = new WordLadderProblem("cat", "dog", WordDictionary.threeLetterWords());
        State start = problem.getInitialState();

        System.out.println("=== Initial state ===");
        System.out.println(start);
        System.out.println("Is it a goal? " + problem.isGoal(start));

        // one action, many next states
        System.out.println("\n=== Next states of the initial state ===");
        for (IAction action : problem.getActions()) {
            System.out.println(action.getName() + ": " + action.apply(start));
        }

        // walk by hand to the goal (this is not the shortest ladder; can you find a shorter one?)
        System.out.println("\n=== Walk by hand to the goal ===");
        String[] path = {"hat", "hot", "dot", "dog"};
        State current = start;
        System.out.print(current);
        for (String word : path) {
            current = moveTo(problem, current, word);
            if (current == null) {
                System.out.println("\nStopped: can not go to \"" + word + "\" from here.");
                return;
            }
            System.out.print(" -> " + current);
        }
        System.out.println("\nIs it a goal? " + problem.isGoal(current));
    }

    // applies the actions and picks the next state with this word (or null)
    private static State moveTo(Problem problem, State state, String word) {
        for (IAction action : problem.getActions()) {
            Collection<State> nextStates = action.apply(state);
            for (State next : nextStates) {
                if (next.toString().equals(word)) {
                    return next;
                }
            }
        }
        return null;
    }
}
