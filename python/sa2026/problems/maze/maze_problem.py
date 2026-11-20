from sa2026.core.heuristic_function import HeuristicFunction
from sa2026.core.i_action import IAction
from sa2026.core.problem import Problem
from sa2026.core.state import State
from sa2026.problems.maze.manhattan_distance import ManhattanDistance
from sa2026.problems.maze.maze import Maze
from sa2026.problems.maze.maze_action import MazeAction
from sa2026.problems.maze.maze_state import MazeState


class MazeProblem(Problem):
    """
    The maze problem: move the player from the start cell to the goal cell.

    Initial state: the player is on 'S'.
    Goal:          the player is on 'G'.
    Actions:       move up, down, left, right (one cell, not into a wall).
    Cost:          every move costs 1.
    Heuristic:     the Manhattan distance to the goal (see ManhattanDistance).
    """

    def __init__(self, maze: Maze):
        # All states share this one maze.
        # This line does NOT copy the maze. It copies the reference,
        # so MazeState.maze points to the same original Maze object.
        MazeState.maze = maze
        self._initial_state = MazeState(maze.start_row, maze.start_col)
        self._heuristic = ManhattanDistance()

        # the order of this list is the order the algorithms try the actions
        self._actions: list[IAction] = [
            MazeAction("Move up", -1, 0),
            MazeAction("Move down", 1, 0),
            MazeAction("Move left", 0, -1),
            MazeAction("Move right", 0, 1),
        ]

    def get_initial_state(self) -> State:
        return self._initial_state

    def is_goal(self, state: State) -> bool:
        return state.is_goal()

    def get_actions(self) -> list[IAction]:
        return self._actions

    # every step costs the same
    def get_action_cost(self, s: State, a: IAction, next_state: State) -> float:
        return 1

    # used by Greedy and A*
    def get_heuristic_function(self) -> HeuristicFunction:
        return self._heuristic
