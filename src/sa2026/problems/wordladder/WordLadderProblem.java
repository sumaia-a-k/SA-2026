package sa2026.problems.wordladder;

import java.util.ArrayList;
import java.util.List;

import sa2026.core.IAction;
import sa2026.core.Problem;
import sa2026.core.State;

/**
 * The word ladder problem: change the start word into the goal word,
 * one letter at a time. Every word on the way must be in the dictionary.
 *
 * Example: cat -> hat -> hot -> dot -> dog
 *
 * Initial state: the start word.
 * Goal:          the goal word.
 * Actions:       change one letter (only one action, but it gives many states).
 * Cost:          every change costs 1.
 */
public class WordLadderProblem extends Problem {

    private final State initialState;
    private final List<IAction> actions = new ArrayList<>();

    public WordLadderProblem(String startWord, String goalWord, WordDictionary dictionary) {
        if (startWord.length() != goalWord.length()) {
            throw new IllegalArgumentException("The start and goal words must have the same length.");
        }
        WordLadderState.setGoalWord(goalWord.toLowerCase());
        initialState = new WordLadderState(startWord.toLowerCase());
        actions.add(new ChangeLetterAction(dictionary));
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

    @Override
    public double getActionCost(State s, IAction a, State next) {
        return 1;
    }
}
