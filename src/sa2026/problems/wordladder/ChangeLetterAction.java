package sa2026.problems.wordladder;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import sa2026.core.IAction;
import sa2026.core.State;

/**
 * The only action of the problem: change ONE letter of the word.
 * The new word must be in the dictionary.
 *
 * Unlike the maze, this one action can give MANY next states:
 *   "cat" -> "bat", "hat", "mat", "cot", "cut", ...
 * This is why IAction.apply() returns a Collection and not one State.
 *
 * The dictionary is kept here (a normal field, not static), because only the action needs it.
 * This is the "other option" we talked about in MazeState.
 */
public class ChangeLetterAction implements IAction {

    private final WordDictionary dictionary;

    public ChangeLetterAction(WordDictionary dictionary) {
        this.dictionary = dictionary;
    }

    @Override
    public Collection<State> apply(State s) {
        String word = ((WordLadderState) s).getWord();
        List<State> nextStates = new ArrayList<>();

        // try every position, and every letter from 'a' to 'z' in that position
        for (int i = 0; i < word.length(); i++) {
            for (char letter = 'a'; letter <= 'z'; letter++) {
                if (letter == word.charAt(i)) {
                    continue; // same letter, not a change
                }
                String newWord = word.substring(0, i) + letter + word.substring(i + 1);
                if (dictionary.contains(newWord)) {
                    nextStates.add(new WordLadderState(newWord));
                }
            }
        }
        return nextStates;
    }

    @Override
    public String getName() {
        return "Change one letter";
    }
}
