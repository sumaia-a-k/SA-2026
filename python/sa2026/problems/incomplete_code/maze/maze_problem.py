from sa2026.core.i_action import IAction
from sa2026.core.problem import Problem
from sa2026.core.state import State
from sa2026.problems.incomplete_code.maze.maze import Maze
from sa2026.problems.incomplete_code.maze.maze_action import MazeAction  # you need it in TODO 2
from sa2026.problems.incomplete_code.maze.maze_state import MazeState


class MazeProblem(Problem):
    """
    STUDENT TASK: finish this class.

    The maze problem: move the player from the start cell to the goal cell.

    Initial state: the player is on 'S'.
    Goal:          the player is on 'G'.
    Actions:       move up, down, left, right (one cell, not into a wall).
    Cost:          every move costs 1.

    There is no heuristic yet. We add it in a later session.

    Search for "TODO" and follow the steps.
    """

    def __init__(self, maze: Maze):
        MazeState.maze = maze  # all states share this one maze

        # TODO 1: create the initial state. The player starts on the start cell.
        #         Hint: MazeState(maze.start_row, maze.start_col)
        self._initial_state = None

        # TODO 2: add the four actions to the list self._actions.
        #         Use these names and changes (row_change, col_change):
        #           "Move up"    (-1,  0)
        #           "Move down"  ( 1,  0)
        #           "Move left"  ( 0, -1)
        #           "Move right" ( 0,  1)
        #         The order of this list is the order the algorithms try the actions.
        self._actions: list[IAction] = []

    def get_initial_state(self) -> State:
        # TODO 3: return the initial state.
        return None

    def is_goal(self, state: State) -> bool:
        # TODO 4: ask the state if it is a goal.
        return False

    def get_actions(self) -> list[IAction]:
        # TODO 5: return the list of actions.
        return None

    # The cost of going from state s to state next_state using action a.
    def get_action_cost(self, s: State, a: IAction, next_state: State) -> float:
        # TODO 6: every step costs the same. Return 1.
        #         Question: what changes if some cells are "mud" and cost 3?
        return 0
