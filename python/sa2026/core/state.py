from abc import ABC, abstractmethod


class State(ABC):
    """
    A state is one situation of the problem.
    Example: in a maze, the state is the player position (row, col).

    Every problem has its own State class that extends this class.
    """

    # True if this state is a goal state
    @abstractmethod
    def is_goal(self) -> bool:
        pass

    # how the state is printed on the screen (Java: toString)
    @abstractmethod
    def __str__(self) -> str:
        pass

    # two states are equal when they describe the same situation (Java: equals)
    @abstractmethod
    def __eq__(self, other: object) -> bool:
        pass

    # must give the same number for equal states (Java: hashCode)
    @abstractmethod
    def __hash__(self) -> int:
        pass

    # How the state is printed inside a list, for example print([s1, s2]).
    # Python uses __repr__ there, not __str__, so we make them the same.
    def __repr__(self) -> str:
        return str(self)

    # Note: here Python is stricter than Java. The methods above are abstract,
    # so Python does not let you create a state that does not have them.
    # One trap: if you write __eq__ but forget __hash__, Python removes the hash,
    # and you get "unhashable type" when the state goes into a set.
    # Without __eq__ and __hash__, graph search can not find repeated states.
