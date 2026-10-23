from sa2026.core.i_action import IAction
from sa2026.core.state import State
from sa2026.problems.incomplete_code.wordladder.word_dictionary import WordDictionary


class ChangeLetterAction(IAction):
    """
    STUDENT TASK: finish this class.

    The only action of the problem: change ONE letter of the word.
    The new word must be in the dictionary.
    """

    def __init__(self, dictionary: WordDictionary):
        # TODO: save the fields you need.
        pass  # "pass" = do nothing. Remove it when you write your code.

    # returns ALL the words we can reach by changing one letter
    def apply(self, s: State) -> list[State]:
        # TODO
        #   Question: in the maze, apply() gives 0 or 1 state. How many can it give here?
        return []

    def get_name(self) -> str:
        return "Change one letter"
