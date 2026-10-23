import string

from sa2026.core.i_action import IAction
from sa2026.core.state import State
from sa2026.problems.wordladder.word_dictionary import WordDictionary
from sa2026.problems.wordladder.word_ladder_state import WordLadderState


class ChangeLetterAction(IAction):
    """
    The only action of the problem: change ONE letter of the word.
    The new word must be in the dictionary.

    Unlike the maze, this one action can give MANY next states:
      "cat" -> "bat", "hat", "mat", "cot", "cut", ...
    This is why IAction.apply() returns a list and not one State.

    The dictionary is kept here (a normal variable, not a class variable),
    because only the action needs it.
    This is the "other option" we talked about in MazeState.
    """

    def __init__(self, dictionary: WordDictionary):
        self._dictionary = dictionary

    def apply(self, s: State) -> list[State]:
        word = s.word
        next_states: list[State] = []

        # try every position, and every letter from 'a' to 'z' in that position
        for i in range(len(word)):
            for letter in string.ascii_lowercase:  # "abcdefghijklmnopqrstuvwxyz"
                if letter == word[i]:
                    continue  # same letter, not a change
                # word[:i] = the letters before position i, word[i + 1:] = the letters after it
                new_word = word[:i] + letter + word[i + 1:]
                if self._dictionary.contains(new_word):
                    next_states.append(WordLadderState(new_word))
        return next_states

    def get_name(self) -> str:
        return "Change one letter"
