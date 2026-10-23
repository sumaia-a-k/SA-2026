from sa2026.core.state import State


class WordLadderState(State):
    """
    STUDENT TASK: finish this class.

    A state of the word ladder problem = the current word, for example "cat".
    """

    # TODO: add the fields you need.
    #       Question: is the goal word part of the state? Where should it be kept?

    def __init__(self, word: str):
        # TODO
        pass  # "pass" = do nothing. Remove it when you write your code.

    def is_goal(self) -> bool:
        # TODO
        return False

    def __str__(self) -> str:
        # TODO: return the word
        return ""

    def __eq__(self, other: object) -> bool:
        # TODO
        return False

    def __hash__(self) -> int:
        # TODO
        #   Question: can we make a hash with no conflicts here, like in MazeState? Why?
        return 0
