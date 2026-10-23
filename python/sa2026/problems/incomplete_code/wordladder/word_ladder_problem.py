from sa2026.core.i_action import IAction
from sa2026.core.problem import Problem
from sa2026.core.state import State
from sa2026.problems.incomplete_code.wordladder.word_dictionary import WordDictionary


class WordLadderProblem(Problem):
    """
    STUDENT TASK: finish this class.

    The word ladder problem: change the start word into the goal word,
    one letter at a time. Every word on the way must be in the dictionary.

    Example: cat -> hat -> hot -> dot -> dog

    Every change costs 1.
    """

    def __init__(self, start_word: str, goal_word: str, dictionary: WordDictionary):
        # TODO: save the fields you need.
        #   Question: what should happen if the two words have different lengths?
        pass  # "pass" = do nothing. Remove it when you write your code.

    def get_initial_state(self) -> State:
        # TODO
        return None

    def is_goal(self, state: State) -> bool:
        # TODO
        return False

    def get_actions(self) -> list[IAction]:
        # TODO
        return []

    def get_action_cost(self, s: State, a: IAction, next_state: State) -> float:
        # TODO
        return 0
