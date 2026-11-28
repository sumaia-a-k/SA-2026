from sa2026.core.i_action import IAction
from sa2026.core.state import State
from sa2026.problems.queens.queens_state import QueensState


class SwapQueensAction(IAction):
    """
    The only action of the 8-queens problem: SWAP two queens.
    The queen of column i takes the row of the queen of column j, and the other way.
    After a swap there is still one queen in every row and every column.
    (Moving ONE queen alone would put two queens in the same row.)

    Like DriveAction, this one action gives MANY next states:
    all the pairs i < j: 8 x 7 / 2 = 28 neighbours.
    The order: swap(0,1), swap(0,2), ..., swap(0,7), swap(1,2), ...
    (the same order as on the lesson page: 1-2, 1-3, ..., 2-3, ...)
    """

    def apply(self, s: State) -> list[State]:
        assert isinstance(s, QueensState)
        next_states: list[State] = []
        for i in range(s.get_size()):
            for j in range(i + 1, s.get_size()):
                next_states.append(s.swap(i, j))
        return next_states

    def get_name(self) -> str:
        return "Swap two queens"
