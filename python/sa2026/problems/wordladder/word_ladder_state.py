from sa2026.core.state import State


class WordLadderState(State):
    """
    A state of the word ladder problem = the current word, for example "cat".
    """

    # The goal word is NOT part of the state. It is the same for all states.
    # Like the maze in MazeState, it is a class variable: one copy for all states.
    # WordLadderProblem sets it once, before the search starts.
    goal_word: str = ""

    def __init__(self, word: str):
        self.word = word  # do not change it after the state is created

    def is_goal(self) -> bool:
        return self.word == WordLadderState.goal_word

    def __str__(self) -> str:
        return self.word

    # two states are equal when they have the same word
    def __eq__(self, other: object) -> bool:
        if self is other:
            return True
        if not isinstance(other, WordLadderState):
            return False
        return self.word == other.word

    # We use the hash of the string itself.
    # Here we do NOT know all the possible values (any word can come),
    # so we let Python make a good hash for us.
    # Compare with MazeState, where we know the ranges and can have no conflicts at all.
    #
    # Note: Python gives a string a different hash each time you start the program
    # (for security). Inside one run it is always the same, and this is all a set needs.
    def __hash__(self) -> int:
        return hash(self.word)
