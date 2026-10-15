package sa2026.problems.incomplete_code.wordladder;

import sa2026.core.State;

/**
 * STUDENT TASK: finish this class.
 *
 * A state of the word ladder problem = the current word, for example "cat".
 */
public class WordLadderState implements State {

    // TODO: add the fields you need.
    //       Question: is the goal word part of the state? Where should it be kept?

    public WordLadderState(String word) {
        // TODO
    }

    @Override
    public boolean isGoal() {
        // TODO
        return false;
    }

    @Override
    public String toString() {
        // TODO: return the word
        return "";
    }

    @Override
    public boolean equals(Object o) {
        // TODO
        return false;
    }

    @Override
    public int hashCode() {
        // TODO
        //   Question: can we make a hash with no conflicts here, like in MazeState? Why?
        return 0;
    }
}
