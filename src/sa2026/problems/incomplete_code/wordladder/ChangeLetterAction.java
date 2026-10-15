package sa2026.problems.incomplete_code.wordladder;

import java.util.Collection;
import java.util.Collections;

import sa2026.core.IAction;
import sa2026.core.State;

/**
 * STUDENT TASK: finish this class.
 *
 * The only action of the problem: change ONE letter of the word.
 * The new word must be in the dictionary.
 */
public class ChangeLetterAction implements IAction {

    // TODO: add the fields you need.

    public ChangeLetterAction(WordDictionary dictionary) {
        // TODO
    }

    // returns ALL the words we can reach by changing one letter
    @Override
    public Collection<State> apply(State s) {
        // TODO
        //   Question: in the maze, apply() gives 0 or 1 state. How many can it give here?
        return Collections.emptyList();
    }

    @Override
    public String getName() {
        return "Change one letter";
    }
}
