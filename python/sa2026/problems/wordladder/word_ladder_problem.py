from sa2026.core.i_action import IAction
from sa2026.core.problem import Problem
from sa2026.core.state import State
from sa2026.problems.wordladder.change_letter_action import ChangeLetterAction
from sa2026.problems.wordladder.word_dictionary import WordDictionary
from sa2026.problems.wordladder.word_ladder_state import WordLadderState


class WordLadderProblem(Problem):
    """
    The word ladder problem: change the start word into the goal word,
    one letter at a time. Every word on the way must be in the dictionary.

    Example: cat -> hat -> hot -> dot -> dog

    Initial state: the start word.
    Goal:          the goal word.
    Actions:       change one letter (only one action, but it gives many states).
    Cost:          every change costs 1.
    """

    def __init__(self, start_word: str, goal_word: str, dictionary: WordDictionary):
        if len(start_word) != len(goal_word):
            raise ValueError("The start and goal words must have the same length.")
        WordLadderState.goal_word = goal_word.lower()
        self._initial_state = WordLadderState(start_word.lower())
        self._actions: list[IAction] = [ChangeLetterAction(dictionary)]

    def get_initial_state(self) -> State:
        return self._initial_state

    def is_goal(self, state: State) -> bool:
        return state.is_goal()

    def get_actions(self) -> list[IAction]:
        return self._actions

    def get_action_cost(self, s: State, a: IAction, next_state: State) -> float:
        return 1
