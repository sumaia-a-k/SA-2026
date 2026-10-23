package sa2026.problems.wordladder;

import sa2026.core.State;

/**
 * A state of the word ladder problem = the current word, for example "cat".
 */
public class WordLadderState implements State {

    /*
     * The goal word is NOT part of the state. It is the same for all states.
     * Like the maze in MazeState, it is static: one copy for all states.
     * WordLadderProblem sets it once, before the search starts.
     */
    private static String goalWord;

    private final String word;

    public WordLadderState(String word) {
        this.word = word;
    }

    public static void setGoalWord(String newGoalWord) {
        goalWord = newGoalWord;
    }

    public String getWord() {
        return word;
    }

    @Override
    public boolean isGoal() {
        return word.equals(goalWord);
    }

    @Override
    public String toString() {
        return word;
    }

    // two states are equal when they have the same word
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof WordLadderState)) return false;
        WordLadderState other = (WordLadderState) o;
        return word.equals(other.word);
    }

    /*
     * We use the hash of the String itself.
     * String.hashCode() uses the prime 31. Here we do NOT know all the possible values
     * (any word can come), so a prime-based hash is a good choice.
     * Compare with MazeState, where we know the ranges and can have no conflicts at all.
     */
    @Override
    public int hashCode() {
        return word.hashCode();
    }
}
