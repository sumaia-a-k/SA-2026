package sa2026.problems.incomplete_code.wordladder;

import java.util.Collections;
import java.util.List;

import sa2026.core.IAction;
import sa2026.core.Problem;
import sa2026.core.State;

/**
 * STUDENT TASK: finish this class.
 *
 * The word ladder problem: change the start word into the goal word,
 * one letter at a time. Every word on the way must be in the dictionary.
 *
 * Example: cat -> hat -> hot -> dot -> dog
 *
 * Every change costs 1.
 */
public class WordLadderProblem extends Problem {

    // TODO: add the fields you need.

    public WordLadderProblem(String startWord, String goalWord, WordDictionary dictionary) {
        // TODO
        //   Question: what should happen if the two words have different lengths?
    }

    @Override
    public State getInitialState() {
        // TODO
        return null;
    }

    @Override
    public boolean isGoal(State state) {
        // TODO
        return false;
    }

    @Override
    public List<IAction> getActions() {
        // TODO
        return Collections.emptyList();
    }

    @Override
    public double getActionCost(State s, IAction a, State next) {
        // TODO
        return 0;
    }
}
