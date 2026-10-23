from abc import ABC, abstractmethod

from sa2026.core.state import State


class IAction(ABC):
    """
    An action is a move that changes one state to another.
    Example: in a maze, "Move up" moves the player one cell up.
    """

    # Applies the action on state s and returns the new states.
    # If the action is not allowed (for example a wall), return an empty list.
    @abstractmethod
    def apply(self, s: State) -> list[State]:
        pass

    # the action name, for example "Move up"
    @abstractmethod
    def get_name(self) -> str:
        pass
